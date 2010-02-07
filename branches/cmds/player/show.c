/* Like, a show command.
   Shows who is tuned into channels.
   See the channel daemon for more details.
   Mobydick, 6-8-98
*/

#include <options.h>
#include <config.h>

#define SYNTAX "Usage: show <channel>\n"

int do_command (string channel) {

    object user ;
    object *dorks ;
    int i, sz;

    if (!channel) return fail_msg(SYNTAX);

    if (member_array(channel, CHANNELS)==-1) {
        write ("There is no such channel as "+channel+".\n") ;
        return 1 ;
    }
    if (member_array(channel, WIZ_CHANNELS)>-1 &&
               !this_user()->query_wizard()) {
        write ("There is no such channel as "+channel+".\n") ;
        return 1 ;
    }
    dorks = CHANNEL_D->listening_to_channel(channel) ;
    if (sizeof(dorks)==0) {
	write ("No one is listening to "+channel+" channel.\n") ;
	return 1 ;
    }
    for (i=0,sz=sizeof(dorks);i<sz;i++) {
	write (dorks[i]->query_name()+" ") ;
    }
    write ("\n") ;
    return 1 ;
}

string help(){
	return SYNTAX+"\n\
This command allows one to observe the current list of\n\
listeners on a given line.";
}
