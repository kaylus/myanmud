/*
 * This is inherited into a player body, and it contains information as to the player's
 * race and gender
 */

#include RACE_KIT;
#define STAGES ({"What gender do you wish to be?\n", "What race do you wish to be?\n" })
string gender, race; /* contain race and gender */
int stage; /* what stage of input we're at */

string query_gender(){
	return (gender) ? gender : (gender = GENDERS[2]);
}

string query_race(){
	return (race) ? race : "raceless";
}

int input(string str){/* this function receives the initial quest for building a body */
	switch(stage){
	case 0: /* gender */
		if(!str || !(({ "male", "female" }) & ({ str }))){
			message("Male or female?\n");
			return 0;
		}
		/* valid gender */
		gender = str;
		stage = 1; /* race */
		message(STAGES[stage]);
		return 0;
        case 1: /* race */
		if(!str || !(RACES & ({ str }))){
			message(implode(RACES, " ")+"\n");
			return 0;
		}
		message("Your race set to "+str+"\n");
		race = str;
		stage = 2; /* forward facing */
		/* pass on to something else? */
		return 1;
	}
}

void init_input(){/* initialize racial/gender setting */
	stage = 0; /* stage 0 = gender */
	message(STAGES[stage]);
}