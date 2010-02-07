/* The summon command.
   Hymael - off of home
   Mobydick, 5-28-94.
*/

#include <config.h>

#define SYNTAX "Usage: summon <player>\n"

int do_command(string str){
    object ob ;

    if(!str)
    	return fail_msg(SYNTAX);

    ob = USERS_D->find_user(lowercase(str));
	catch(ob = ob->query_player());
	if(!ob)
		return fail_msg("Player "+capitalize(str)+" not found.\n");

	if(ob->query_environment() == TP->query_environment()){
		write(capitalize(str)+" is already with you.\n");
		return 1;
	}
	if(!catch(ob->move(TP->query_environment()))){
		write("You summon "+capitalize(str)+" to you.\n");
		ob->catch_tell(TPN+" summons you!\n");
		return 1;
	}
    return fail_msg("Summon failed.\n");
}

string help(){
	return SYNTAX+"\n\
This command allows wizards to translocate other persons to their\n\
location.";
}