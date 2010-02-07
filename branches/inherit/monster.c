/***************************
 *       monster.c         *
 * Hymael - monster coding *
 ***************************/
#include <config.h>
#include <type.h>

#define AGGRESSIVE  1 	/* critter is aggro */
#define COM_ENABLED 2	/* commands enabled */
#define FOLLOWS     4   /* critter follows if fighting */

inherit father OBJECT;
inherit body   BODY;

private static int    _bits;         /* our monster's attributes */
private static string greeting;      /* to be displayed upon player entrance */
private static string gender;

void create(){/* master init */
	body::roll_stats();
	init_health();
	set_heart_beat(5);/* may hinge speed on something set in monster */
	add_event("death");
	body::create();
}

int is_monster(){ return 1; }

int query_living(){/* so it accepts inputs */
	return 1;
}

void set_aggressive() { _bits |= AGGRESSIVE;       }
int query_aggressive(){ return _bits & AGGRESSIVE; }

void enable_commands()      { _bits |= COM_ENABLED;       }
int query_commands_enabled(){ return _bits & COM_ENABLED; }

void set_follow()               { _bits |= FOLLOWS;           }
int query_follow(object player) {
	return ( (_bits & FOLLOWS) && query_attacking(player) );
}

void set_id(string *newid){/* assures we always have id monster */
    ::set_id (newid + ({ "monster" }) );
}

void set_gender(string val){ gender = val; }

string query_gender(){ return gender; }

string query_cap_name(){ return capitalize(short_desc); }

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

/*********
 * thump *
 *********/
void heart_beat(){
	do_tick();
#if 0
	if(query_in_combat() && round_resolution()){/* kung fu action */
		execute_attack();
	}else{
		unblock_attack(1);
	}
#endif
}

/****************************************
 * croak - create corpse, move to here, *
 * populate, destruct                   *
 ****************************************/
void die(){
	object corpse, *stuff;
	int sz;

    corpse = clone_object(CORPSE);
    corpse->set_name(query_cap_name());
    corpse->move(environment);
    /* move inventory to the corpse */
    stuff = query_inventory() ;
	if (stuff && (sz = sizeof(stuff)) > 0){
		while(--sz>=0){
		    stuff[sz]->move(corpse);
		}
    }
    environment->room_tell(query_cap_name()+" dies.\n");
    event("death");
    destruct();
}

string query_name(){
	return short_desc;
}

void set_greeting(string str){ greeting = str; }

/* command() is called by the user object any time the player sends
   a string that is neither an input_to nor an editor. It finds the
   appropriate command bin and calls it. Hymael - proudly made this
   fucker more efficient
 */
int command(string str){
    string verb, arg;

	/* Only the associated user object and the force command call this. */
	if(!query_commands_enabled())
		return 0;

    if(!str || str=="")
		return 0;

	if(sscanf(str, "%s %s", verb, arg) != 2)
		verb = str;

    if(file_exists("/cmds/player/"+verb+".c")){/***PLAYER BIN***/
		if(call_other("/cmds/player/"+verb, "do_command", arg))
			return 1;
    }

    if(!arg){/***MOVE?***/
		mapping exits;
		exits = environment->query_exits();
		if(exits && exits[verb]){
			if(call_other("/cmds/player/go","do_command", verb))
				return 1;
		}
	}
	{/***VC OBS***/
	object *obs;
	int i;
    if(environment){/***ROOM***/
		if(environment->perform_action(verb,arg))
			return 1;

		if((obs = environment->query_inventory()) && (i = sizeof(obs)) > 0){/***ROOM INVENTORY***/
			while(i--){
				if(obs[i]->perform_action(verb, arg))
					return 1;
			}
		}
    }
    if((obs = query_inventory()) && (i = sizeof(obs)) > 0){/***INVENTORY***/
	    while(i--){
	    	if(obs[i]->perform_action(verb, arg))
	    		return 1;
		}
	}
	}/***VC END***/

    if(SOUL_D->do_soul(str))
    	return 1;

    return 0;
}

int do_command(string str){
	int res;
	object tp;
	tp = TP;
	/* set this_player, later make sure this is necessary */
    USERS_D->set_this_player(TO);
    res = command(str);
    /* set this_player */
    USERS_D->set_this_player(tp);
    return res;
}

/************************************
 * called when a player enters room *
 ************************************/
void greet(object player){
	if(query_aggressive()){/* commence annihilation */
		do_command("kill "+player->query_name());
	}
	if(greeting){
		catch(call_other(this_object(), greeting, player));
	}
}

/*************************************
 * our monster's ears on the world   *
 * through this we can parse up some *
 * nasty behaviors                   *
 *************************************/
void catch_tell(string str){
	string tmp1, tmp2, tmp3;
	object player;
	/* player entered our room
	   Hymael - may make this be passable to a function defined in the monster
	 */
	if(!str)
		return;

	if(sscanf(str, "%s said, \""+query_cap_name()+", %s\"", tmp1, tmp2) == 2){
		call_out("do_command", 0.7, tmp2);
	}
	if(sscanf(str, "%s enters", tmp1)==1){
		player=USERS_D->find_user(lowercase(tmp1));
		player=player->query_player();
		if(player){
			greet(player);/* our monster's greeting mechanism */
		}
	/*} else if(sscanf(str, "%s waves", tmp1)==1){
		player=USERS_D->find_user(lowercase(tmp1));
		if(player){
			do_command("tell "+lowercase(tmp1)+" don't wave at me");
		}
	/*} else if(sscanf(str, "%s drops %s %s.", tmp1, tmp3, tmp2)==3){
		call_out("do_command",0.5,("get "+tmp2));*/
	} else if(sscanf(str, "%s leaves %s.", tmp1, tmp2)==2){
		player=USERS_D->find_user(lowercase(tmp1));
		catch(player = player->query_player());
		if(player && query_follow(player)){/* follow */
			call_out("do_command",0.3,("go "+tmp2));
		}
			/*if(tmp1=="Hymael"){

				player->catch_tell(capitalize(query_cap_name())+" follows you.\n");

			}*/
	}/* else if(sscanf(str, "%s dies.", tmp1)==1){/* hack for now */
		/*player=USERS_D->find_user(lowercase(tmp1));
		catch(player = player->query_player());
		if(player && query_is_attacking(player)){/* we don't attack dead people */
		/*	stop_attacking(player);
		}
	}*/

}

string flip_dir(string dir){
	if(member_array(dir, A_DIRS) > -1){
		return DIRS[dir];
	}
	return nil;
}

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
    /*TO->catch_tell(environment->query_long(brief));*/

	if(silent) return;

	if(direction && direction != ""){
		string from;
		if(old_env)
			old_env->room_tell(query_cap_name() + " leaves " + direction + ".\n");

		from = "";
		from = flip_dir(direction);
		if(from) from = " from the " + from;

		dest->room_tell(query_cap_name() + " enters" + from + ".\n", ({ TO }) ) ;
	} else {
		if (old_env)
			old_env->room_tell(query_cap_name() + " vanishes into the shadows.\n");

		dest->room_tell(query_cap_name() + " appears from the shadows.\n", ({ TO }) );
	}
}

string query_long() {
    string ret;

   	ret = capitalize(query_subjective())+" is the monster "+query_cap_name()+
   		  query_xa()+"\n"+ father::query_long();
    ret += body::query_long();

    return ret ;
}