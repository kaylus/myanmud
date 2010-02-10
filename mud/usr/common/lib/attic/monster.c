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
inherit body   BODY_LIB;

private static int    bit_att;       /* our monster's attributes */
private static string greeting;      /* to be displayed upon player entrance */

void create(int clone){/* master init */
	body::create(clone);
}

int is_monster(){ return 1; }

int query_living(){/* so it accepts inputs */
	return 1;
}

void set_aggressive() { bit_att |= AGGRESSIVE;       }
int query_aggressive(){ return bit_att & AGGRESSIVE; }

void enable_commands()      { bit_att |= COM_ENABLED;       }
int query_commands_enabled(){ return bit_att & COM_ENABLED; }

void set_follow()               { bit_att |= FOLLOWS;           }
int query_follow(object player) {
	return ( (bit_att & FOLLOWS) && this_object()->query_is_attacking(player) );
}

void set_id(string *newid){/* assures we always have id monster */
    ::set_id (newid + ({ "monster" }) );
}

string query_cap_name(){ return capitalize(short_desc); }

string query_Name(){ return capitalize(short_desc); }

string query_name(){ return short_desc; }
/*
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
}*/

/*********
 * thump *
 *********/
void evt_heart_beat(object obj){
	/* monster events? */
::evt_heart_beat(obj);
}

#if 0
/****************************************
 * croak - create corpse, move to here, *
 * populate, destruct                   *
 ****************************************/
void die(){
	object corpse, *stuff;
	int sz;
	
	if(!find_object(CORPSE)compile_object(CORPSE);
	
    corpse = clone_object(CORPSE);
    corpse->set_name(query_Name());
    corpse->move(this_object()->query_environment());
    /* move inventory to the corpse */
    stuff = this_object()->query_inventory() ;
	if (stuff && (sz=sizeof(stuff))>0) {
		while(--sz>=0){
		    stuff[sz]->move(corpse);
		}
    }
    this_object()->query_environment()->message(query_Name()+" dies.\n");
    event("death");
    destruct();
}
#endif
/*****************************
 * mask it up to handle shit *
 *****************************/
/*int receive_damage(int damage, object dealer, varargs string type){
	int hp, ret;
	USERS_D->set_this_player(TO);
	if(health::query_health() < 0)return 0;
	ret = health::receive_damage(damage, dealer, type);
	hp = health::query_health();
	if(hp < 0){

		call_out("die", 0);
	}
	USERS_D->set_this_player(previous_object());
	/* possibly this will be where death occurs */
/*	return ret;
}*/


void set_greeting(string str){ greeting=str; }

/*****************************************
 * monster's can issue commands as well, *
 * note return value 1 is success        *
 *****************************************/
int input (string str) {/*TODO: may need to set this player */
    string verb, arg;
    int i, sz, result ;
    object *obs ;
    object me;

	/*if(!query_commands_enabled()) return 0;*/
	
	return ::input(str);
}

/************************************
 * called when a player enters room *
 ************************************/
void greet(object player){
	if(query_aggressive()){/* commence annihilation */
		input("kill "+player->query_name());
	}
	if(greeting){
		catch(call_other(this_object(), greeting, player));
	}
	/*if(greeting){
		player->catch_tell(greeting+"\n");/* expand later to room echo */
	/*}
	/* test */
	/*do_command("wave");
	do_command("say I'm sexy");*/
}

/*************************************
 * our monster's ears on the world   *
 * through this we can parse up some *
 * nasty behaviors                   *
 *************************************/
void message(string str){
	string tmp1, tmp2, tmp3;
	object player;
	/* player entered our room
	   Hymael - may make this be passable to a function defined in the monster
	 */
	if(!str)return;
	if(sscanf(str, "%s said, \""+query_cap_name()+", %s\"", tmp1, tmp2)==2){
		call_out("do_command",0.7,tmp2);
	}
	if(sscanf(str, "%s enters", tmp1)==1){
		player=find_player(lowercase(tmp1));
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
		player=find_player(lowercase(tmp1));
		catch(player = player->query_player());
		if(player && query_follow(player)){/* follow */
			call_out("input",0.3,("go "+tmp2));
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
	string ret;
	mapping dirs;
	dirs = ([
				"east":"west",
				"south":"north",
				"west":"east",
				"north":"south"
			]);
	ret="";
	if(member_array(dir, map_indices(dirs))!=-1){
		ret=dirs[dir];
	}
	return ret;
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
    res = ::move(dest) ;
    if (res) {
	/* Let the player take a peek at his new environment */

	if (silent) return res ;

        if (direction && direction!="") {
	    if (old_env) old_env->room_tell(capitalize(query_cap_name()) +
			   " leaves "+direction+".\n") ;
		from = "";
		from = flip_dir(direction);
		if(from!="")from = " from the "+from;
	    dest->room_tell(capitalize(query_cap_name())+" enters"+from+".\n",
	    	({ this_object() }) ) ;
        } else {
	    if (old_env) old_env->room_tell(capitalize(query_cap_name())+
		          " vanishes into the shadows.\n") ;
            dest->room_tell(capitalize(query_cap_name())+" appears from the shadows.\n",
			    ({ this_object() }) ) ;
	}
    }
    return res;
}

/* Hymael - trying to implement atomic */
atomic int move (mixed dest, varargs string direction, int silent) {

    object old_env ;
    int res ;
    string from;

    if (!dest) error("No destination.\n");
    old_env = query_environment() ;
    if (typeof(dest)==T_STRING) {
        dest=get_object(dest) ;
    }
    ::move(dest);
    /* Let the player take a peek at his new environment */
    /*O->catch_tell(environment->query_long(brief)) ;*/

	if(silent) return 1;

	if (direction && direction != "") {
		if (old_env) old_env->message(query_Name() +
			   " leaves "+direction+".\n") ;
		from = "";
		from = flip_dir(direction);
		if(from != "")from = " from the "+from;
		dest->message(query_Name()+" enters"+from+".\n",
			({ this_object() }) ) ;
	} else {
		if (old_env) old_env->message(query_cap_name()+
			  " vanishes into the shadows.\n") ;
		dest->message(query_Name()+" appears from the shadows.\n",
			({ this_object() }) ) ;
	}
    return 1;
}
#endif
/*************************
 * check the sexay boday *
 *************************/
string query_long() {
    string ret, describe, *indices, *windices;
    int i, total, sz;
    object *inventory, *worn_items, *wielded_items;

    ret = this_object()->query_Name() + " ( " + query_xa() + " )\n";

    if ((describe = father::query_long())) ret += "\n" + describe;
    ret += body::query_long();
    return ret ;
}
/* override */
int attack(object target){
	int res;
	res = ::attack(target);
	if(res == 1){
		subscribe_event(target, "death");
	}
	return res;
}

/********************
 * so monster stops *
 * assaulting dead  *
 * people           *
 ********************/
/*void evt_death(mixed dead){ stop_attacking(dead[0]); }*/

