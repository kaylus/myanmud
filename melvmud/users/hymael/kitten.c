/*
 *
 */

#include <config.h>

inherit OBJECT ;

int broke;

void create() {
set_short ("[35m[1ma gay kitten[0m") ;
set_long ("This is a lovely pink kitten with a penchant for gayness.\n") ;
set_id(({"kitten", "gay kitten"})) ;
    if (!clone_num(this_object())) return ;
    set_heart_beat(5) ;
}

void heart_beat() {

    object foo ;
	string str;

    foo = query_environment() ;
    set_heart_beat(random(4)+4) ;
    if(broke){
		str="The kitten comes to, having used another of its lives.";
		broke=0;
	}
	else{
		switch(random(6)){
			case 0:str="The kitten does a somersault and lands on its back, snapping it like a twig.";
					set_heart_beat(34);
					broke =1;
					break;
			case 1:str="The kitten meows.";
					break;
			case 2:str="You smell a foul wind.  You suspect the gay kitten.";
					break;
			case 3:str="The kitten bats around a ball of yarn.";
					break;
			case 4:str="The kitten purrs and wraps around your ankles.";
					break;
			case 5:str="The kitten licks itself in perverse ways.";

		}
	}

	foo->room_tell("[35m[1m"+str+"\n[0m");
}

