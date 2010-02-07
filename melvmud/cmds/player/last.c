/* Last command
   Query the given last
   -Hymael
*/

#include <options.h>
#include <config.h>

#define SYNTAX "Usage: last <channel>\n"

int do_command (string str) {
    string *log;
    int i,x;
    if(!str)fail_msg(SYNTAX);
 	/* check if it's a daemon channels */
	if (member_array(str, CHANNELS)>-1) {
		if (member_array(str, WIZ_CHANNELS)>-1 &&
					   !TP->query_wizard()) {
			return fail_msg(SYNTAX);
		} else {
			log = CHANNEL_D->query_backlog(str) ;
		}
    } else {
		log = TP->query_backlog(str);
	}
 	if (!log) {
        return fail_msg(SYNTAX);
    }
    write("Backlog of "+str+":\n");
    i=sizeof(log);
    if(i){
		for(x=0;x<i;x++)write(log[x]);
	} else {
		write("None.\n");
	}
    return 1 ;
}

string help(){
	return SYNTAX+"\n\
This command returns the given channel's backlog\n";
}