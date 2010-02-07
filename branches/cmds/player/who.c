/* The who command. Kinda bare-bones right now. */

#include <config.h>

int do_command() {

    string foo ;
    string *names ;

    write ("The following users are logged on: \n") ;
    names = USERS_D->query_user_names() ;
    foo = implode(names,", ") ;
    write (foo+"\n") ;
    return 1 ;
}

string help(){
	return "Usage: who\n\n\
This command lists all the players online at the time.";
}