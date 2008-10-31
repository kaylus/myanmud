/*
 * This is inherited into a player body, and it contains information as to the player's
 * race and gender
 */

#include <race_kit.h>
#define STAGES ({"What gender do you wish to be?\n", "What race do you wish to be?\n" })
string gender, race; /* contain race and gender */
int stage; /* what stage of input we're at */

string query_gender(){
	return (gender) ? gender : (gender = GENDERS[2]);
}

string query_race(){
	return (race) ? race : "raceless";
}

object input_to(string str){/* this function receives the initial quest for building a body */
	switch(stage){
	case 0: /* gender */
		if(!str || !sizeof(({ "male", "female" }) & ({ str }))){
			this_object()->message("Male or female?\n");
			return this_object();
		}
		/* valid gender */
		gender = str;
		stage = 1; /* race */
		this_object()->message(STAGES[stage]);
		return this_object();
        case 1: /* race */
		if(!str || !sizeof(RACES & ({ str }))){
			this_object()->message(implode(RACES, " ")+"\n");
			return this_object();
		}
		this_object()->message("Your race set to "+str+"\n");
		race = str;
		stage = 2; /* forward facing */
		/* pass on to something else? */
		return nil;
	}
	return nil;
}

void init_input(){/* initialize racial/gender setting */
	stage = 0; /* stage 0 = gender */
	this_object()->message(STAGES[stage]);
}

object input_done(){
	this_object()->move(ROOMD->query_start_room(), "");
	return nil;/* get out of input to object code */
}