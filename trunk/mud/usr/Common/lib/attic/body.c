/*******************************************************
 *                   body.c                            *
 * This will hold the functionality of equipping items *
 * in specific slots                                   *
 * and other bodily functions                          *
 * -Hymael                                             *
 *******************************************************/
#include <config.h>
#include <type.h>
#include <kernel/kernel.h>
#include <game/body.h>

#define WIELDS ({ "primary", "secondary" })
#define ARMORS ({ "suit", "gauntlets", "gloves", "greaves", "ring", "helm",\
"cloak", "shoulder", "waist", "feet", "shield" })


/* direction mappings */
#define DIRS ([ "east" : "west", "south" : "north", "west" : "east", "north" : "south" ])
#define A_DIRS ({ "east", "west", "south", "north" })

inherit container CONTAINER;
inherit WEAPON;
inherit combat COMBAT;
inherit health HEALTH;
inherit STATS; /* temp */
/*inherit PLAY_TOOL;*/
inherit RACE_KIT;
inherit WEALTH;
inherit SKILLS;
inherit BODY_INPUT;
inherit alias ALIAS; /* alias toolbox, move lib into System? */

/**************************************
 * mapping of worn items - to be made *
 * non static at some point           *
 **************************************/
private static mapping worn;

/************************************
 * wielded["primary"]=weapon object *
 ************************************/
static mapping wielded;

static int ac;               	/* this will be our body's armor class */
object user;                /* contain user object? */
							/* do we need a list of users who've used this body? Live in accountd? */
object end_room;            /* last room that held this body */
int stasis;

void create(int clone){ 
    object heartd;
    if(!clone) return;
    if(!worn)
	worn      = ([]);

    if(!wielded)
	wielded     = ([]);

    /***WEIGHT STUFF***/
    set_bulk(200);
    set_weight(200);
    set_capacity(150);
    set_volume(150);

    ac = 0;

    roll_stats(); /* temp */

    combat::create();
	alias::create();
    init_health();
    /*user = previous_object();*/
    /*set_id(({ user->query_name() }));*/

    /* heart beat */
    heartd = find_object(HEARTD);
    if(!heartd)heartd = compile_object(HEARTD);

    subscribe_event(heartd, "heart_beat");

    add_event("death");
	ACCOUNTD->add_body(this_object());
	stasis = 0;
}
/* TODO: add query_objective */
string query_subjective(){
    switch(query_gender()){
    case "male":
	return "he";
    case "female":
	return "she";
    }
    return "it";
}

string query_possessive(){
    switch(query_gender()){
    case "male":
	return "his";
    case "female":
	return "her";
    }
    return "its";
}

/* work horse of player messages, replaces catch_tell */
int message(string str){
    if(user)
	return user->message(str);

    return 0;
}

void stasis(){/* put body into stasis */
	/*if(!SYSTEM() && !KERNEL())
		error("Illegal call to stasis body.\n");*/
		
    end_room = environment;

    this_object()->move(ROOMD->query_meat_locker(), "", 1, 1);/* stored, should also lock up call_outs 
	                                                             on the body at this time */
    end_room->message(user->query_Name()+" enters stasis.\n");
	stasis = 1;
}

void awaken(object obj){/* this function needs to wake up call_outs and everything too */
    /*if(!SYSTEM() && !KERNEL())
		error("Illegal call to awaken body.\n");*/

    if(user != obj){/* check if this is what we want to do? Should we tell ACCOUNTD? */
		LOGD->log("Switching "+object_name(this_object())+"'s user to "+obj->query_Name(), "users");
		user = obj;
	}
    if(!end_room){/* room is no more */
	end_room = ROOMD->query_start_room(); /* set to start room */
    }

    user->message("Your body awakens.\n");/* stupid message? Just show room? */
    end_room->message(user->query_Name()+" enters the room from stasis.\n");
    this_object()->move(end_room, "", 1, 1);
	stasis = 0;
}

void evt_heart_beat(object obj){
    catch(this_object()->do_tick());
    catch(this_object()->do_round());
}

int allow_subscribe(object obj, string name){
    return 1;
}

int query_ac(){
    return ac + this_object()->query_stat("dexterity");
}/* add in attribute checks */

void set_id(string *newid){/* assures we always have id weapon */
    container::set_id (newid);
}

int is_body(){ return 1; }

void incr_ac(int val){ ac += val; }
void decr_ac(int val){ ac -= val; }

object query_primary(){
    if(!wielded) wielded=([]);
    return wielded[WIELDS[0]];
}

object query_secondary(){
    if(!wielded) wielded=([]);
    return wielded[WIELDS[1]];
}

/******************************************
 * outside we call this to push onto worn *
 * values : 0 fail, 1 success             *
 ******************************************/
atomic void set_worn(object obj){/* calculate armor total ac */
    string type;
    if(!wielded) wielded=([]);
    if(!worn)    worn   =([]);
    type = obj->query_type();
    if(type && !worn[type]){
	if(type == "shield" && wielded[WIELDS[1]]){
	    error("You haven't the hands to equip that.\n"); /* can't equip shield over weapon */
	}
	if(worn[type])error("You have something else worn in that slot.\n");
	worn[type]=obj;
	incr_ac(obj->query_ac());
	return;
    }
    error("You can't equip that.\n");
}

void set_user(object obj){
	/*TODO security */
	user = obj;
    set_id(({ user->query_name() }));
}

/* returns controlling user object */
object query_user(){
    return user;
}
/* these functions should digress fluidly if no user object is decided on */
string query_Name(){
    return (user)?user->query_Name():"Nameless";
}

string query_name(){
    return (user)?user->query_name():"nameless";
}

string query_short(){
    return query_Name();
}
/****************
 * and a query  *
 ****************/
int query_worn(object obj){/* remove ac */
    object *values;
    if(!wielded) wielded = ([ ]);
    if(!worn)    worn   = ([ ]);

    values = map_values(worn);
    if(values && member_array(obj, values)>-1){
	return 1;
    }
    return 0;
}


int handle_break(object owner, varargs object armor, int damage){
    return 0; /* so we don't break */
}

/**********
 * remove *
 **********/
atomic void remove_worn(object obj){
    object *values;
    string *indices;
    int i;
    if(query_worn(obj)){
	values = map_values(worn);
	indices = map_indices(worn);
	i = member_array(obj, values);
	worn[indices[i]] = nil;
	decr_ac(obj->query_ac());
	return;
    }
    error("You can't do that.\n");
}

/*******************************
 * query listing of worn items *
 *******************************/
mapping query_worn_listing(){
    return worn;
}


/*************************
 * wield some shit       *
 *  1- success           *
 *  0- fail by no slot   *
 * -1- fail by twohander *
 * -2- fail by shield    *
 *************************/
atomic void wield( object obj ){
    if(!wielded) wielded=([]);
    if(!worn)    worn   =([]);
    if(!obj->is_weapon()) error("No slot for that weapon.\n");

    if(obj->query_two_handed()){
	if(!wielded[WIELDS[0]] && !wielded[WIELDS[1]] &&
	  !worn["shield"]){/* wield this beastly two hander */
	    wielded[WIELDS[0]] = obj;
	    wielded[WIELDS[1]] = 1; /* placeholder, note when unwielding 2hander */
	    return;
	}else{
	    error("That weapon requires two hands to wield.\n");
	}
    }else if(!obj->query_is_offhand()){
	if(!wielded[WIELDS[0]]){
	    wielded[WIELDS[0]] = obj;
	    return;
	}else if(wielded[WIELDS[0]]->query_is_offhand() && !worn["shield"] &&
	  !wielded[WIELDS[1]]){/* push to second and wield */
	    wielded[WIELDS[1]] = wielded[WIELDS[0]];
	    wielded[WIELDS[0]] = obj;
	    return;
	}else{
	    error("You haven't the hands to wield that.\n");
	}
    }else{
	if(!wielded[WIELDS[0]]){
	    wielded[WIELDS[0]] = obj;
	    return;
	}else if(!wielded[WIELDS[1]]){
	    if(!worn["shield"]){
		wielded[WIELDS[1]] = obj;
		return;
	    }else{
		error("You already have a shield equipped.\n");
	    }
	}
    }
	error("Cannot wield that at this time.\n");
}

/****************
 * and a query  *
 ****************/
int query_wielded(object obj){
    object *values;
    if(!wielded) wielded=([]);
    if(!worn)    worn   =([]);

    values = map_values(wielded);
    if(values && member_array(obj, values)>-1){
	return 1;
    }
    return 0;
}

/**********
 * remove *
 **********/
atomic void unwield(object obj){
    object *values;
    string *indices;
    int i;
    if(!wielded) wielded=([]);
    if(!worn)    worn   =([]);

    if(query_wielded(obj)){
	values = map_values(wielded);
	indices = map_indices(wielded);
	i = member_array(obj, values);
	wielded[indices[i]]=nil;
	if(obj->query_two_handed()){
	    wielded[WIELDS[1]]=nil;
	}else if(wielded[WIELDS[1]] && !wielded[WIELDS[0]]){/* move secondary to primary */
	    wielded[WIELDS[0]] = wielded[WIELDS[1]];
	    wielded[WIELDS[1]] = nil;
	}
	return;
    }
    error("You haven't that equipped.\n");
}
#if 0
/****************************
 * overloads for container  *
 * these now check for worn *
 * and wielded items        *
 ****************************/
int release_object (object ob) {
    /* check equipped, if so, unequip it */
    int res, func, fun;
    res = ::release_object(ob);/* pass the ball */
    if(res && query_worn(ob)){/* don't like doing messages here, but fuck it */
	remove_worn(ob);
	catch(fun = call_other(ob, ob->query_unequip_func()));
	if(!fun){/* messages not handled */
	    this_object()->message("You unequip "+ob->query_weapon_name()+".\n");
	    this_object()->query_environment()->messsage(
	      this_object()->query_Name()+" unequips "+ob->query_weapon_name()+".\n",
	    ({ this_object() }) );
	}
    }else if(res && query_wielded(ob)){
	unwield(ob);
	catch(fun = call_other(ob, ob->query_unwield_func()));
	if(!fun){/* messages not handled */
	    this_object()->message("You unwield "+ob->query_weapon_name()+".\n");
	    this_object()->query_environment()->message(
	      this_object()->query_Name()+" unwields "+ob->query_weapon_name()+".\n",
	    ({ this_object() }) );
	}
    }
    return res; /* propogate through */
}
#endif
atomic void release_object(object ob, varargs int slide){
    /* check equipped, if so, unequip it */

    ::release_object(ob, slide);  /* pass the ball */

    if(query_worn(ob) ||
    (ob->query_type() == "shield" &&
      query_wielded(ob))){/* don't like doing messages here, but fuck it */
	remove_worn(ob);
	if(catch(call_other(ob, ob->query_unequip_func()))){/* messages not handled */
	    this_object()->message("You unequip "+ob->query_short()+".\n");
	    this_object()->query_environment()->message(
	      this_object()->query_Name()+" unequips "+ob->query_short()+".\n",
	    ({ this_object() }) );
	}
    }else if(query_wielded(ob)){
	unwield(ob);
	if(catch(call_other(ob, ob->query_unwield_func()))){/* messages not handled */
	    this_object()->message("You unwield "+ob->query_weapon_name()+".\n");
	    this_object()->query_environment()->message(
	      this_object()->query_Name()+" unwields "+ob->query_weapon_name()+".\n",
	    ({ this_object() }) );
	}
    }

}

/*************************
 * check the sexay boday *
 *************************/
string query_long() {
    string ret, describe, *indices, *windices;
    int i, total, sz;
    object *inventory, *worn_items, *wielded_items;

    inventory = this_object()->query_inventory() ;
    ret = "";
    total = 0;
    if (wielded){
	wielded_items = map_values(wielded);
	windices = map_indices(wielded);
	for(i=0,sz=sizeof(windices);i<sz;i++){
	    if(!wielded[windices[i]] || wielded[windices[i]]==1)
		continue;
	    ret += "\n"+pad(capitalize(windices[i])+": ",15)+
	    wielded[windices[i]]->query_short();
	    total++;
	}
    }
    if (worn){
	worn_items = map_values(worn);
	indices = map_indices(worn);
	for(i=0,sz=sizeof(indices);i<sz;i++){
	    ret += "\n"+pad(capitalize(indices[i])+": ",15)+worn[indices[i]]->query_short();
	}
	total += sz;
    }
    ret += "\n";
    if (!inventory || ((sz=sizeof(inventory))-total)==0) {
	ret += capitalize(this_object()->query_subjective())+" is not carrying anything.\n" ;
    } else {
	ret += capitalize(this_object()->query_subjective())+" is carrying:\n" ;
	for (i=0;i<sz;i++) {
	    if(worn_items && member_array(inventory[i], worn_items)>-1)continue;
	    if(wielded_items && member_array(inventory[i], wielded_items)>-1)continue;
	    ret += "  "+inventory[i]->query_short()+"\n" ;
	}
    }
    return ret ;
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
/* input command decipherer */
int input(string str){
    string cmd, args, fail_msg;
    mixed ret_fail;
    object *inv;
    fail_msg = "";

    if(sscanf(str, "%s %s", cmd, args) < 2){
	cmd = str;
	args = "";
    }

    /* do some alias stuff */
    if(user->query_alias(cmd) != cmd && (!user->query_wiztool() || !query_editor(user->query_wiztool()))){/* found alias */
	string argx;
	cmd = user->query_alias(cmd);
	if(sscanf(cmd, "%s %s", cmd, argx) > 0){/* have args */
	    args = argx + args;
	}
    }

    /* return is as follows
	 *  1 - action done, end command search
	 *  nil - continue seek
	 *  string - fail string, continue seek
     */

    /* body bin, make this a loop */

    /* channeld check */
    catch{
	if(find_object(CHANNELD)->cmd_channel(cmd, args) == 1) return 1;
    }

    if (function_object("cmd_" + cmd, this_object()))
	catch(ret_fail = call_other(this_object(), "cmd_" + cmd, args));/* change to call_limited? */



    switch(typeof(ret_fail)){
    case T_STRING:/* fail string, continue seek */
	fail_msg = ret_fail;
    case T_NIL:/* continue seek */
	break;
    default: /* done */
	return 1;
    }

    /* other bins... */
    /* room/body inventory bin */
    /* error checking */
    inv = ({});
    if(query_environment()){ 
	inv += ({ query_environment() });
	if(query_environment()->query_inventory()) 
	    inv += query_environment()->query_inventory();
    }

    if(query_inventory())
	inv += query_inventory();

    inv -= ({ this_object() });

    if(sizeof(inv)){
	int i;
	i = sizeof(inv);
	while(--i>=0){

	    if(function_object("perform_action", inv[i]))
		ret_fail = call_other(inv[i], "perform_action", cmd, args);

	    switch(typeof(ret_fail)){
	    case T_STRING:/* fail string, continue seek */
		fail_msg = ret_fail;
	    case T_NIL:/* continue seek */
		break;
	    default: /* done */
		return 1;
	    }
	}
    }
	
	if(query_environment() && query_environment()->query_exit(str)){
		cmd = "go";
		ret_fail = this_object()->cmd_go(str);
		switch(typeof(ret_fail)){
	    case T_STRING:/* fail string, continue seek */
		fail_msg = ret_fail;
	    case T_NIL:/* continue seek */
		break;
	    default: /* done */
		return 1;
	    }
	}

    if(!strlen(fail_msg))
	return 0;

    message(fail_msg);/* failed to find command */
    return 1;
}
#endif

/* Hymael - trying to implement atomic, eventually dest will just be objs */
atomic void move(mixed dest, varargs string direction, int silent, int nolook){
    object old_env;

    if(!dest)
	error("No destination.\n");

    old_env = environment;
    if (typeof(dest) == T_STRING){
	dest = find_object(dest);
    }
    ::move(dest);

    if(!nolook){
	/* Let the player take a peek at his new environment, add in brief support? */
	this_object()->message(environment->query_long());
    }

    if(silent) return;

    if(direction && direction != ""){
	string from;
	if(old_env)
	    old_env->message(query_Name() + " leaves " + direction + ".\n");

	from = flip_dir(direction);
	if(from != "") from = " from the " + from;

	dest->message(query_Name() + " enters" + from + ".\n", ({ this_object() }) ) ;
    } else {
	if (old_env && old_env != dest)
	    old_env->message(query_Name() + " vanishes into the shadows.\n");

	dest->message(query_Name() + " appears from the shadows.\n", ({ this_object() }) );
    }
}
