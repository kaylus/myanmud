/* The tune command. For channels. See /system/channel_d.c for details
   Mobydick, 6-5-98
*/
#include <options.h>
#include <config.h>

#define SYNTAX "Usage: tune <channel>\n"

int do_command (string channel) {

    object user ;

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
    user = this_player()->query_user() ;
    if (CHANNEL_D->user_listening_to_channel(user, channel)) {
	CHANNEL_D->remove_user_from_channel(user, channel) ;
	TP->tune_channel(channel, 0);
	write ("Tuning out "+channel+".\n") ;
    } else {
	CHANNEL_D->add_user_to_channel(user, channel) ;
	TP->tune_channel(channel, 1);
	write ("Tuning in "+channel+".\n") ;
    }
    return 1 ;
}

string help(){
	return SYNTAX+"\n\
This command is used to toggle yourself for attending\n\
the given channel.";
}