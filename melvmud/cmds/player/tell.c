/* The tell command. Used to send a message to another player. */

#include <config.h>

#define SYNTAX "Usage: tell <name> <message>\n"

int do_command (string str) {

    string name, message, mess ;
    object target ;

    if (!str || replace_string(str," ","")=="" || sscanf(str,"%s %s",name,message)!=2 ||
    	replace_string(message," ","")=="") {
	return fail_msg(SYNTAX);
    }
    target = USERS_D->find_user(name) ;
    if (!target) {
	return fail_msg(capitalize(name)+" is not logged on right now.\n");
    }
    target = target->query_player() ;
    if (target==previous_object()) {
	return fail_msg("You strike up a conversation with yourself.\n");
    }
    write (TP->query_color("tell")+"You tell "+capitalize(name)+", \""+
    	capitalize(message)+"\"[0m\n") ;
    name = previous_object()->query_name() ;
    mess = target->query_color("tell")+capitalize(name)+" tells you, \""+
    	capitalize(message)+"\"[0m\n";
    target->catch_tell(mess) ;
    mess = replace_string(mess, " tells you, ", " told you, ");
    target->add_backlog("tell", mess);
    return 1 ;
}

string help(){
	return SYNTAX+"\n\
This command is used to send a message to the specified\n\
person.";
}