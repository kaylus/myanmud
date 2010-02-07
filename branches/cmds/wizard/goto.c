/* The goto command.
   Mobydick, 5-28-94.
*/

#include <config.h>

#define SYNTAX "Usage: goto <room name or player>\n"

int do_command (string str) {

    string file, tmp, res;
    object ob ;

    if (!str) return fail_msg (SYNTAX);
	file = str ;
    if (!absolute_path(file)) file = previous_object()->query_cwd()+file ;
    file = resolve_path(file) ;
    if (file[strlen(file)-2..strlen(file)-1]!=".c") file += ".c" ;
    if (previous_object()->query_environment()) {
        tmp = object_name(previous_object()->query_environment())+".c" ;
    } else {
	tmp = "" ;
    }
    if (tmp=="/"+file) {
	write ("You twitch.\n") ;
	return 1 ;
    }
    if (!file || file_exists(file)<1) {
	ob = USERS_D->find_user(str) ;
	if (!ob) return fail_msg("You must supply a room or player name as argument.\n");
	ob = ob->query_player()->query_environment() ;
	if (ob==previous_object()->query_environment()) {
	    write ("You twitch.\n") ;
	    return 1 ;
	}
	res = catch(previous_object()->move(ob));
	if (res) {
	    write (res);
	}
	return 1 ;
    }
    res = catch(previous_object()->move(file));
    if (res) {
        write ("You remain where you are.\n") ;
    }
    return 1 ;
}
