/* Ye olde help command. It takes a string arg and mores a file in
   /doc/help with that name to the user. If the user passes no arg,
   then /doc/help/introduction is sent.
   Mobydick, 8-6-94.
   Hymael - expanding to query help in commands
*/

#include <config.h>
#include <admin.h>

#define PLAYER_CMD "/cmds/player/"
#define WIZ_CMD "/cmds/wizard/"
#define ADM_CMD "/cmds/admin/"
#define BANNER "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\
-=-=-=\n"

/* for querying into directory and invoking help() */

int do_command (string str) {
	string temp, helper;
    if (!str || str=="") str="introduction" ;
    temp = HELP_DIR + str ;
    if (!file_exists(temp)) {
		/* start querying command directories */
		temp = PLAYER_CMD + str +".c";
		if(file_exists(temp) && (helper=temp->help())){
			write(BANNER+"Help for "+temp+"\n"+BANNER+helper+"\n");
			return 1;
		}
		if(previous_object()->query_privileges()=="admin" ||
			previous_object()->query_privileges()=="wizard"){
			temp = WIZ_CMD + str + ".c";
			if(file_exists(temp) && (helper=temp->help())){
				write(BANNER+"Help for "+temp+"\n"+BANNER+helper+"\n");
				return 1;
			}
		}
		if(previous_object()->query_privileges()=="admin"){
			temp = ADM_CMD + str + ".c";
			if(file_exists(temp) && (helper=temp->help())){
				write(BANNER+"Help for "+temp+"\n"+BANNER+helper+"\n");
				return 1;
			}
		}
        return fail_msg("There is no help available on that topic.\n");
    }
    previous_object()->more_file(temp) ;
    return 1 ;
}
