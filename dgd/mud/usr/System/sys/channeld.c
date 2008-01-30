/*
 * channeld
 * this daemon handles all channel functionality, it may talk with logd
 * to make more useful reporting of errors and events
 */
#include <kernel/user.h>
#define CHANS ([ "wiz" : ({}), "myan" : ({}) ])

mapping backlogs, channels; /* a mapping of the backlogs of channels, and  tuned users */
				  /* people tuned? or add an inherited for user.c */

void create(){/* inits */
	backlogs = channels = CHANS;
}

/* a request for tuning of a channel, do previous_object check?
 * 0 = cannot tune, -1 = tuned out, 1 = tuned in
 */
int tune(string channel){
	int i;

	if(!channel || (i = member_array(channel, map_indices(channels))) == -1 || !previous_object()->is_body()){
		LOGD->log("Channel improper.\n", "channel");
		return 0;
	}

	/* check if previous_object() can tune channel */
	if(channel == "wiz" && !previous_object()->query_wiztool()){/* be sure it's a wiz */
		return 0;
	}

	/* check if previous_object() is tuned? */


	/* flip tune */
	if(member_array(previous_object(), channels[channel]) > -1){
		channels[channel] -= ({ previous_object() });
		return -1;/* tuned out */
	}

	channels[channel] += ({ previous_object() });
	return 1;
}

/* show users tuned to a channel returns a printable string */
string show(string channel){
	int i;
	object player;
	string *indies, ret;

	/* check if previous_object() can tune channel */
	if(channel == "wiz" && !previous_object()->query_wiztool()){/* be sure it's a wiz */
		return "You can't check this line.\n";
	}

	if(member_array(channel, map_indices(channels)) == -1){
		return "Invalid channel id.\n";
	}

	if(!channels[channel]){
		return "No one tuned into channel: " + channel + ".\n";
	}

	indies = channels[channel];
	ret = "Channel <" + channel + "> is currently listened to by:\n";
	for(i = sizeof(indies); i-- > 0;){
		player = find_player(indies[i]);
		if(player) ret += player->query_Name() + " ";
	}

	return ret + "\n";
}


/* valid tunes */

/* broadcast_channel */
void broadcast(string channel, string message, varargs object except){
	int emote, i;
	object *listeners;

	if(!channels[channel] || !message || !strlen(message))
		return;

	if(member_array(previous_object(), channels[channel]) == -1){/* not tuned in */
		return;
	}

	/* do emotes? */
	if(message[0] == ':'){
		emote = 1;
		message = message[1..];
	}

	listeners = channels[channel] - ({ except });
	for(i = sizeof(listeners); i--; ){
		listeners[i]->message((emote) ? "[" + channel + "] " + previous_object()->query_Name() + " " + message + "\n" :
				                        previous_object()->query_Name() + " [" + channel + "] " + message + "\n");

	}
}

mapping get_channels(){
	return channels;
}

/* tune out all, function used to log someone out */

/* tune in at log in */
