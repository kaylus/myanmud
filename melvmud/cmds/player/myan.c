/* myan.c
   A command to provide a Myan channel.
   For details, take a look at the channel daemon, /system/channel_d.c
   Mobydick, 6-9-98
   Hymael, 3-15-03
*/

#include <config.h>

int do_command (string str) {

    object sender ;

    sender = this_player()->query_user() ;
    if (!sender) {
        fail_msg ("non-interactives can't send.\n") ;
        return 0 ;
    }
    if (CHANNEL_D->user_listening_to_channel(sender, "myan")!=1) {
        write ("You're not tuned into that channel.\n") ;
        return 1 ;
    }
    CHANNEL_D->send_channel_message(sender, "myan", str) ;
    return 1 ;
}

string help(){
	return "Usage: myan <message>\n\n\
This is the Myan line, use it to speak to fellow\n\
Myans.";
}
