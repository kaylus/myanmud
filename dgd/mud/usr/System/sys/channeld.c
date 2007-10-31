/*
 * channeld
 * this daemon handles all channel functionality, it may talk with logd
 * to make more useful reporting of errors and events
 */
#define CHANS ({ "wiz", "myan" })

string *channels; /* an array of active channels */
mapping backlogs; /* a mapping of the backlogs of channels */
				  /* people tuned? or add an inherited for user.c */

void create(){/* inits */
	backlogs = ([]);
	channels = CHANS;
}

int tune(string channel){/* a request for tuning of a channel, do previous_object check? */
	int i;

	if(!channel || (i = member_array(channel, channels)) == -1){
		return 0;
	}

	/* check if previous_object() is tuned */

	/* check if previous_object() can tune channel */

	/* flip tune */
	return 1;
}
