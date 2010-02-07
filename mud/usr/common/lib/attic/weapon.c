/******************
 *    weapon.c    *
 ******************/
#include <config.h>

#define TYPES ({ "cut", "pierce", "blunt" })
/***********************************
 * eventually we need weapon types *
 * for what damage they deal       *
 ***********************************/

#define OFF_HAND 1 /* bit for off hand */
#define TWO_HAND 2 /* bit for two hand */
/* attributes */

inherit OBJECT;

static string type;         			/* of TYPES */
static int bit_att;                     /* a bitfield of attributes */
static int *damage_matrix; 			    /* handles damage output */
static int accuracy;        			/* inherent accuracy, barring player attributes */
static string hit_func;     			/* function called each hit to handle special */
static string wield_func;   			/* function called when weapon is wielded */
static string unwield_func; 			/* function called when weapon is unwielded */
static string *verbs_me, *verbs_other;  /* "You verbs_me[num] X with your query_short()"*/

static string weapon_name;              /* work around */

int is_weapon(){
	/*if(this_object()->is_body()){
		return 0;
	}*/
	return 1;
}

void set_weapon_name(string val){ weapon_name = val; }

string query_weapon_name(){
	if(weapon_name) return weapon_name;
	if(this_object()->is_body()) return "fists";
	return this_object()->query_short();
}

void set_two_handed(){ bit_att |= TWO_HAND; }

int query_two_handed(){ return bit_att & TWO_HAND; }

void set_type(string str){ type = str; }

string query_type(){
	if(!type) return "blunt";
	return type;
}

void set_offhand(){ bit_att |= OFF_HAND; }

int query_is_offhand(){ return bit_att & OFF_HAND; }

void set_accuracy(int val){ accuracy = val; }

int query_accuracy(){ return accuracy; }

void set_hit_func(string str){ hit_func = str; }

string query_hit_func(){ return hit_func; }/* must accept (object attacker, object attackee) */

void set_wield_func(string str){ wield_func = str; }

string query_wield_func(){ return wield_func; }

void set_unwield_func(string str){ unwield_func = str; }

string query_unwield_func(){ return unwield_func; }

/***********************************************
 *          NOTE ON UN/WIELD FUNCTIONS         *
 * if the function returns 1, the message is   *
 * dealt with, if not, message still must be   *
 * done                                        *
 ***********************************************/

void set_verbs_me(string *str)   { verbs_me = str;    }
void set_verbs_other(string *str){ verbs_other = str; }

string *query_verbage(){/* returns 2 dimensional string with a random verb(me and other) */
	int i;
	if(verbs_me && (i = sizeof(verbs_me))){
		i = random(i);
		if(verbs_other && verbs_other[i]){
			return ({ verbs_me[i], verbs_other[i] });
		}else{
			return ({ verbs_me[i], verbs_me[i]+"s" });
		}
	}
	/* return defaults */
	return ({ "hit", "hits" });
	/*************************************************************************************************************************
	 *  								FORM																				 *
	 *	hitter - "You "+verbage[0]+" "+target_name+" with your "+weapon->query_short()+" and...                              *
	 *	room -   attacker_name+" "+verbage[1]+" "+target_name+" with "+attacker_possessive+" "+weapon->query_short()+" and...*
	 *	target - attacker_name+" "+verbage[1]+" you with "+attacker_possessive+" weapon->query_short()+" and...              *
	 *************************************************************************************************************************/
}


void set_damage(int *dam){
	/*****************************
	 * ideally we have this form *
	 * ({ 2, 3 })                *
	 * 0 is range, 1 is minimum  *
	 *****************************/
	damage_matrix = dam;
}

int query_damage(){
	int dam;
	if(!damage_matrix)return random(2)+1;
	dam = random(damage_matrix[0]) + damage_matrix[1];
	return dam;
}

void set_id(string *newid){/* assures we always have id weapon */
    ::set_id (newid + ({ "weapon" }) );
}