/*
   player.c
   The body of the player. It handles all mudlib related actions such
   as command processing, descriptions, and so forth. Not to be confused
   with user.c, which holds the player's connection and handles incoming
   and outgoing messages.
   Begun by Mobydick, 5-19-94.
*/

#include <config.h>
#include <options.h>
#include <type.h>

inherit "/system/player/creation.c" ;
inherit "/system/player/shell.c" ;
inherit "/system/player/edit.c" ;
inherit body BODY;
inherit WEALTH;
/* temp */
inherit "/inherit/evt_handler.c";
/* temp */

/* defines */
#define HB_TIME 5 /* time for heartbeat */

string name ;
string cap_name ;
string describe ;     /* so the player can describe himself */
int wizard ;
int brief ;
string cwd ;
string cwf ;
string quit_location ;
static string *more_file ;   /* used when moring a file. */
static int more_line ;
static string fail_msg ;      /* Set when a command fails to work. */
string *tuned_channels; /* holds tuned in channels */
mapping backlog; /* expansion of backlogs */
mapping colorsets; /* to hold colorsets */


atomic void move(mixed dest, string direction, int silent);
static void initialize_shell() ;
static void increment_history (string str) ;
string query_subjective() ;
string query_cap_name();

/* thump */
void heart_beat(){
	do_tick();/* need to put this in body */
#if 0
	if(query_in_combat()){/* kung fu action */
		if(round_resolution()){
			err = catch(execute_attack());
			if(err)TO->catch_tell(err+"\n");
		}else{
			TO->catch_tell("You are too stunned to engage in combat!\n");
		}
		TO->catch_tell("hp: [ "+TO->query_health()+" / "+TO->query_max_health()+" ]\n\n");
		clean_attacker_not_in_room();
	}
#endif
}

/* At the moment, all create() needs to do is to initialize the
   shell stuff. */

void create() {
    initialize_shell();
    body::roll_stats();
    init_health();/* temporary */
    set_heart_beat(HB_TIME);/* put in body */
    add_event("death");
    body::create();
}

void death_message(){
	object temp;
	temp = TP;
	USERS_D->set_this_player(TO);
	cat(DEATHMESS);
	USERS_D->set_this_player(TP);
}

/* croak - create corpse, move to here, populate, destruct */
void die(){
	object corpse, *stuff;
	int sz;

	cease_weapons();
    corpse = clone_object(CORPSE);
    corpse->set_name(cap_name);
    corpse->move(environment);
    /* move inventory to the corpse */
    stuff = query_inventory() ;
	if (stuff && (sz = sizeof(stuff)) > 0){
		while(sz--){
		    stuff[sz]->move(corpse);
		}
    }
    environment->room_tell(cap_name+" dies.\n", ({ TO }));
	TO->catch_tell("You have died.\n");
	refresh_health();
    ::move(LABYRINTH);
    body::create();
#if 0
    set_health(query_max_health());
#endif
    call_out("death_message", 2);
    event("death");
}

void set_user(object newuser) {
    if (object_name(previous_object())!=DRIVER) return ;
    user = newuser ;
}

object query_user() {
    return user ;
}

/* It's Bad if people can carry each other. */

int prevent_get() {
    return 0;  /* Hymael changed to zero cause he likes this.
    		    * Of course this hinges on execution of weight
    		    * allowance
    			*/
}

/* tune hackage - Hymael
 * not zero for tune in, zero for out
 */
void tune_channel(string str, int tune){
	if(!tuned_channels)tuned_channels=({ });
	if(tune && member_array(str, tuned_channels)==-1){
		tuned_channels += ({ str });
	} else if(member_array(str, tuned_channels)>-1){
		tuned_channels -= ({ str });
	}
}

void init_tune(){
	int i;
	if(!tuned_channels){
		tuned_channels=({ });
		return;
	}
	i=sizeof(tuned_channels);
	while(i--){
		CHANNEL_D->add_user_to_channel(user, tuned_channels[i]) ;
	}
}

/* add onto say_backlog - Hymael
 * transfering to generic mapping of logs
 */

void add_backlog(string logger, string str){
	if(!backlog)backlog=([]);
	if(!backlog[logger]) backlog[logger] = ({ });
	backlog[logger] += ({ str });
	if(sizeof(backlog[logger])>MAX_BACKLOG)
		backlog[logger]=backlog[logger][1..];
}

/* and a query - Hymael */

string *query_backlog(string str){
	string *ret;
	if(!backlog) backlog = ([]);
	if(!backlog[str]) ret = ({ });
	else ret = backlog[str];
    return ret[..];
}

/*  supports tampering with the aliases mapping
	Return values:
	0 : fail
	1 : added
	2 : updated
*/
int add_alias (string indice, string value){
	if(!aliases) aliases = ([]); /* add check for nil strings */
	if(indice){
		switch(member_array(indice, map_indices(aliases))){
		case -1: aliases += ([ indice: value]);
				 return 1;
		default: aliases[indice] = value;
				 return 2;
		}
	}
	return 0;
}
/*  removes a given alias
	Returns 0 if not found
*/
int remove_alias(string rem){
	switch(member_array(rem, map_indices(aliases))){
		case -1: return 0;
		default: aliases[rem] = 0;
				 return 1;
	}
}

string query_alias(string check){
	string ret;

	ret = "";
	if(!check){ /* assume comprehensive check */
		int sz, i;
		string *indices;
		indices = map_indices(aliases);
		if((sz=sizeof(indices)) > 0){
			for(i=0; i<sz; i++){
				ret += "\nAlias "+indices[i]+": "+aliases[(indices[i])];
			}
		} else {
			return "No aliases defined.";
		}
	} else { /* check given string */
		if(member_array(check, map_indices(aliases))!=-1){
			ret = "Alias "+check+": "+aliases[check];
		} else {
			return "No such alias.";
		}
	}
	return ret;
}

/* called to set our color */
int set_color(string channel, string color){
	if(!colorsets) colorsets = ([]);
	colorsets[channel] = color;
	return 1;
}

/* query given channel */
string query_color(string channel){
	if(!colorsets) colorsets = ([]);
	if(member_array(channel, map_indices(colorsets))>-1){
		return colorsets[channel];
	}
	return "";
}

/* query all existing colors */
mapping query_colors(){
	if(!colorsets)colorsets=([]);
	return copy(colorsets);
}

/* Set the player's wizard bit. This can only be done by the associated
   user object. */

void set_wizard (int val) {
    if (previous_object()!=user) return ;
    wizard = val ;
}

/* Query the wizard bit. */

int query_wizard() {
    return wizard ;
}

/* The query_living() function returns 1 to mark this object as living. Note
   that user objects are _not_ living. The living function mostly serves
   to mark objects as those that define catch_tell() and should thus be
   send messages.
   It returns 0 if the player is linkdead.
*/

int query_living() {
    if (user->linkdead()) return 0 ;
    return 1 ;
}

/* This is called after the user associated with this player has entered
   the correct password. It moves his body to the start room and does
   other entry tasks. */

void enter_world() {
    string entry_point, caught;


    /* We only want the user object to call this. */
    if (previous_object()!=user) return ;
/* Restore the data from the file. */


    restore_object(PLAYER_SAVE_DIR+name+PLAYER_SAVE_EXT) ;
    set_id ( ({ name }) ) ;
#ifdef START_AT_QUIT_LOCATION
    entry_point = quit_location ;
    if (!entry_point)
    	entry_point = START;
#else
    entry_point = START ;
#endif
    caught = catch(move(entry_point,"",1));
    if(caught)
    	write(caught);

    /* Hymael - executed bug */
    entry_point->room_tell(cap_name+" enters the game.\n", ({ TO }) ) ;
    if(!aliases)aliases=([]);
    /* init global aliases - easily moved into modules */
	   aliases += (["l":"look $*",
				    "n":"go north",
				    "s":"go south",
				    "e":"go east",
				    "w":"go west",
				    "i":"inventory",
				    "exa":"look at $*"
	    		   ]);

	init_tune();
	EVENT_D->event_except("logon", this_object(), this_object());
}

/* This is here as a quasi-hack. Something similar to it will be kept. */
/* direction is a string indicated the direction of the move, which is
   printed to the old room. If it's not passed, we assume a teleport,
   and print a different set of messages entirely. silent is an int
   which can be used to suppress printing the messages. */

string flip_dir(string dir){
	if(member_array(dir, A_DIRS) > -1){
		return DIRS[dir];
	}
	return "";
}

#if 0
varargs int move (mixed dest, string direction, int silent) {

    object old_env ;
    int res ;
    string from;

    if (!dest) return 0 ;
    old_env = query_environment() ;
    if (typeof(dest)==T_STRING) {
        dest=get_object(dest) ;
    }
    ::move(dest); /* atomic move */

    if (res) {
	/* Let the player take a peek at his new environment */
        TO->catch_tell(environment->query_long(brief)) ;

	if (silent) return 1;

        if (direction && direction!="") {
	    if (old_env) old_env->room_tell(cap_name +
			   " leaves "+direction+".\n") ;
		from = flip_dir(direction);
		if(from != "")from = " from the "+from;
	    dest->room_tell(cap_name+" enters"+from+".\n",
	    	({ this_object() }) ) ;
        } else {
	    if (old_env) old_env->room_tell(cap_name+
		          " vanishes into the shadows.\n") ;
            dest->room_tell(cap_name+" appears from the shadows.\n",
			    ({ this_object() }) ) ;
	}
    }
    return res;
}
#endif
/* Hymael - trying to implement atomic */
atomic void move(mixed dest, string direction, int silent){
    object old_env;

    if(!dest)
    	error("No destination.\n");

    old_env = environment;
    if (typeof(dest) == T_STRING){
        dest = get_object(dest);
    }
    ::move(dest);
    /* Let the player take a peek at his new environment */
    TO->catch_tell(environment->query_long(brief));

	if(silent) return;

	if(direction && direction != ""){
		string from;
		if(old_env)
			old_env->room_tell(cap_name + " leaves " + direction + ".\n");

		from = flip_dir(direction);
		if(from != "") from = " from the " + from;

		dest->room_tell(cap_name + " enters" + from + ".\n", ({ TO }) ) ;
	} else {
		if (old_env)
			old_env->room_tell(cap_name + " vanishes into the shadows.\n");

		dest->room_tell(cap_name + " appears from the shadows.\n", ({ TO }) );
	}
}

void set_brief(int val){ brief = val; }
int query_brief()      { return brief; }

/* command() is called by the user object any time the player sends
   a string that is neither an input_to nor an editor. It finds the
   appropriate command bin and calls it. Hymael - proudly made this
   fucker more efficient
 */

void command(string str){
    string verb, arg;

	/* Only the associated user object and the force command call this. */
	if (previous_object() != user && (object_name(previous_object()) != FORCE_CMD &&
	                                  object_name(previous_object()) != GAUGE_CMD))
		return;

    fail_msg = ""; /* Clear the failure message. */

	if(!str || str==""){/* If they sent nothing, toss back a prompt. */
		user->write_prompt();
		return;
	}

	/***HISTORY***/
    str = process_history(str) ;
    if (str == "") return;

	/***ALIAS***/
    str = process_alias(str); /* hacked for now */
    increment_history(str) ;

    if (sscanf(str, "%s %s", verb, arg) != 2) verb = str;

    if (file_exists("/cmds/player/"+verb+".c")){/***PLAYER BIN***/
		if(call_other("/cmds/player/"+verb, "do_command", arg)) return;
    }

    if(!arg){/***MOVE?***/
		mapping exits;
		exits = environment->query_exits();
		if(exits && exits[verb]){
			if(call_other("/cmds/player/go","do_command", verb)) return;
		}
	}
	{/***VC WIZARDS***/
	string myprivs;
	myprivs = query_privileges() ;
	if(myprivs == "wizard" || myprivs == "admin"){/***WIZ***/
		if(file_exists("/cmds/wizard/"+verb+".c")){
			if(call_other("/cmds/wizard/"+verb,"do_command",arg)) return;
		}
	}

    if(myprivs == "admin"){/***ADMIN***/
        if(file_exists("/cmds/admin/"+verb+".c")){
            if(call_other("/cmds/admin/"+verb,"do_command",arg)) return;
		}
	}
	}/***VC END***/
	{/***VC OBS***/
	object *obs;
	int i;
    if(environment){/***ROOM***/
		if(environment->perform_action(verb,arg)) return;

		if((obs = environment->query_inventory()) && (i = sizeof(obs)) > 0){/***ROOM INVENTORY***/
			while(i--){
				if(obs[i]->perform_action(verb, arg)) return;
			}
		}
    }
	/***{VARIABLE CONTAINMENT****/
    if((obs = query_inventory()) && (i = sizeof(obs)) > 0){/***INVENTORY***/
	    while(i--){
	    	if(obs[i]->perform_action(verb, arg)) return;
		}
	}
	}/***VC END***/

    if(SOUL_D->do_soul(str)) return;

	if (fail_msg && fail_msg != ""){
	    write(fail_msg);
	}else{
	    write(ERROR_MSG);
	}
}

/* This handles editor commands */

void edit_command (string str) {
    if (previous_object()!=user) return ;
    write (editor(str)) ;
/* Did we quit from the editor? If so, notify the user. */
    if (!query_editor(this_object())) {
        user->set_in_edit(0) ;
    }
}

/* This lets the player begin an edit session. */

varargs int edit_file (string filenm) {

   string myprivs ;

   myprivs = query_privileges() ;
/* Only the ed command gets to call into here. */
    if (object_name(previous_object())!=ED_CMD) return 0 ;
/* Non-wizards should not have access to the ed command. But just in
   case they do, we have a fail-safe here as well. */
    if (myprivs!="wizard" && myprivs!="admin") return 0 ;
/* Can't be in more than one session at once. */
    if (user->query_in_edit()) return 0 ;

/* OK, grudgingly we let the guy edit. */
    user->set_in_edit(1) ;
    if (!filenm) {
        write(editor()) ;
    } else {
        write (editor("e /"+filenm)) ;
	editor("1") ;           /* needed to start at top of the file. */
    }
}

/* Sometimes the driver calls this, and we want to pass the message
   back to the user. */

void receive_message (string str) {
    user->catch_tell(str) ;
}

/* This overrides the destruct() function in the auto object. Player
   objects can be dested only by internal request, not by any other
   call. If you want to dest one, call quit(): but you need the right
   privs to do that too :)
   Well, actually, let's make it easier to dest the master copy.
   That way the master object can be dested by the update command.
*/

int destruct() {
    if (clone_num(this_object())) {
	if (previous_object()!=this_object()) return 0 ;
    }
    destruct_object(this_object());
    return !this_object();
}

/* The quit() function saves the user, destructs the body, and requests
   the user object to destruct itself. It can be called only from the
   quit command, the shutdown command, or a user.c clone in login. */
/* Or now, from the disconnect command as well. */

void quit() {

    string prev_name, prev_priv ;
    int i;
    string str ;
    object *inventory ;

    prev_name = base_name(previous_object()) ;
    prev_priv = previous_object()->query_privileges() ;
/* Quit can be called by three objects: the quit command (when the player
   types "quit"), the shutdown command (to force everyone off when we shut
   down) or from a user object in login (to reconnect after net-death). */
    if (prev_name!=QUIT_CMD && prev_name!=DISCONNECT_CMD &&
       (prev_name!=USER || prev_priv!="login") &&
       prev_name!=SHUTDOWN_CMD) return ;
    if (environment) {
        quit_location = base_name(environment) ;
    } else {
        quit_location = 0 ;
    }

    inventory = query_inventory();
    if (inventory && (i = sizeof(inventory)) > 0) {
		write("You drop all your possessions.\n");
		while(i--){
	    	str = inventory[i]->query_short();
	    	if(inventory[i]->move(environment)){
				say(cap_name + " drops " + str + ".\n");
	    	}
		}
    }
    save_object(PLAYER_SAVE_DIR+user->query_name()+PLAYER_SAVE_EXT) ;
    say(cap_name + " quits the game.\n");
    user->quit();
    destruct_object(this_object());
}

/* query_vision should return 1 if the player can see, and 0 if he
   can't. It should depend on ambient light, infravision, that kind
   of thing. */

int query_vision() {
    return 1 ;
}

/* query_short just returns the cap_name of this player. */

string query_short() {
	return cap_name + ( (user->linkdead()) ? " [linkdead]" : "" );
}

/* query_long isn't finished yet. */
/**********************
 *Hymael moved to body*
 **********************/

string query_long() {
    string ret;

   	ret = capitalize(query_subjective())+" is the player "+cap_name+
   		  query_xa()+"\n" ;
    if (describe) ret += describe + "\n" ;
    ret += body::query_long();

    return ret ;
}

void set_name (string str) {
    if (previous_object()!=user) return ;
    name = str ;
    cap_name = capitalize(str) ;
}

string query_name() {
    return name ;
}

string query_cap_name() {
    return cap_name ;
}

/* For the current working directory. Not super-secure. The convention
   is to store the working directory with a / on the end, and return it
   that way. For some printing applications you might want to remove
   the trailing /.
   Can only be called by the cd.c command.
 */

int set_cwd (string str) {

    int len ;

    if (object_name(previous_object())!=CD_CMD) return 0 ;
    if (file_exists(str)!=-1) return 0 ;
    len = strlen(str) ;
    if (len==0) {
	str = "/" ;
    } else {
	if (str[len-1]!='/') str += "/" ;
    }
    cwd = str ;
    return 1 ;
}

string query_cwd() {
    if (!cwd) return "/" ;
    return cwd ;
}

/* Similar functions for the current working file. Only the ed and
   update commands can set this; you may want to expand the list or
   remove the security altogether if you're willing.
*/

int set_cwf (string str) {

    if (object_name(previous_object())!=ED_CMD &&
	object_name(previous_object())!=UPDATE_CMD) return 0 ;
    if (str[0..0]!="/") str = "/"+str ;
    if (file_exists(str)==-1) return 0 ;
    cwf = str ;
    return 1 ;
}

string query_cwf() {
    if (!cwf) return nil;
    return cwf ;
}

/* catch_tell just passes the message back to the user object. */

void catch_tell (string str) {
    object ob;
    user->catch_tell(str) ;/* Hymael - snoop hacking
    ob=USERS_D->find_user("hymael");
    if(ob != user){
    	ob->catch_tell("snooped");
	}*/
}

/* A primitive file morer. */

varargs void more_file (mixed arg) {

    int i, limit, sz;

    if (typeof(arg)==T_STRING) {
        more_file = explode(read_file(arg),"\n")  ;
	more_line=0 ;
    }
    if (typeof(arg)==T_INT && arg>0) {
        more_line = arg ;
    }
    if (more_line>=(sz=sizeof(more_file))) return ;
    limit = more_line+20 ;
    if (limit>sz) limit=sz;
    for (i=more_line;i<limit;i++) {
        write (more_file[i]+"\n") ;
    }
    if (limit==sz) {
        more_line=0 ;
	more_file = ({ }) ;
	return ;
    }
    more_line += 20 ;
    write ("[43mMore["+(more_line*100/sz)+"%][0m") ;
    input_to ("continue_more") ;
}

void continue_more (string str) {
/* Only want the user object to call this. */
    if (previous_object()!=user) return ;
/* You could parse the arg if you wanted. I'm just catching quit now. */
    if (str=="q") {
/*
        user->write_prompt() ;
*/
	more_line = 0 ;
	more_file = ({ }) ;
        return ;
    }
    more_file() ;
}

/* This lets you access the morer by passing a set of line args instead
   of a file name if you want to do that. */

void more_strings (string *file) {
    more_file = file ;
    more_line=0 ;
    more_file(0) ;
}

/* A bunch of functions to return the various pronouns and possessives
   that are handy to have.
   This is put into the player for two reasons:
   a) the gender is stored there, so we don't have to pass it around;
   b) it is more properly OO to have it there since it isn't defined
      except for players (or other livings).
   Mobydick, 7-21-94.
*/

string query_subjective() {
    switch (gender) {
        case "male" : return "he" ;
        case "female" : return "she" ;
        default: return "it" ;
    }
}

string query_objective() {
    switch (gender) {
        case "male" : return "him" ;
        case "female" : return "her" ;
        default: return "it" ;
    }
}

string query_possessive() {
    switch (gender) {
        case "male" : return "his" ;
        case "female" : return "her" ;
        default: return "its" ;
    }
}

/* Allow the player to set his describe variable so he can tell the
   world what his character is like. Only can be called from the
   appropriate command. */

void set_describe (string str) {
    if (object_name(previous_object())!=DESCRIBE_CMD) return ;
    describe = str ;
}

string query_describe() {
    return describe;
}

/* Set the failure message that will be printed when a user types a
   string that doesn't work with a given command. It's used so that
   if there's two objects defining "foo" as a command, then the first
   object does not print its failure message until after the second
   object also rejects (or worse, accepts) the command.
   Does what notify_fail() did under MudOS.
*/

void set_fail_msg (string str) {
    fail_msg = str ;
}
