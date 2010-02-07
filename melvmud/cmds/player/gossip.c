/* wiz.c
   A command to provide a wizard channel.
   For details, take a look at the channel daemon, /system/channel_d.c
   Mobydick, 6-9-98
*/

#include <config.h>

int do_command (string str) {

    object sender ;

    sender = this_player()->query_user() ;
    if (!sender) {
	return fail_msg("non-interactives can't send.\n");
	}
    if (CHANNEL_D->user_listening_to_channel(sender, "gossip")!=1) {
	write ("You're not tuned into that channel.\n") ;
	return 1 ;
    }
    CHANNEL_D->send_channel_message(sender, "gossip", str) ;
    return 1 ;
}

string help(){
	return "Usage: gossip <message>\n\n\
Allows you to speak over the gossip channel, if you have\n\
already tuned it in.";
}