/*
 * Logger, log daemon, for your all purpose error logging, debugging,
 * and tree harvesting needs - Hymael
 * TODO:  Add ability for wiz to listen in on logs
 */
#include <kernel/kernel.h>
#define LOG_EXT ".log"
#define LOG_DIR "/logs"
#define DEFAULT LOG_DIR + "/general" + LOG_EXT
#define STAMP "- <"+timestamp+"> "+prev_obj+" "+user_name+":\n\t"
#define DEBUG  /* debug mode */

void log(string mess, varargs string type){
	string timestamp, prev_obj, user_name;
	int sendto;
	if(type && strlen(type)){/* place in appropriate file, may add checking to make sure this isn't exploited */
		if(sscanf(type, "%*s..%*s"))/* possible exploit, ignore for now */
			return;
		type = LOG_DIR + "/" + type + LOG_EXT;
	}else{
		type = DEFAULT;
	}
	timestamp = ctime(time())[4..];
	prev_obj = object_name(previous_object());
	if(this_user()){
		user_name = this_user()->query_Name();
		sendto = 1;
	}else if(previous_program()){
		user_name = previous_program();
	}else{
		user_name = "?System?";
	}

	/* stamp message */
	mess = STAMP + mess + "\n\n";
	/* HAcK */
	if(sendto)
		this_user()->message(mess);
	/* now append to file */
	write_file(type, mess);
        #ifdef DEBUG
find_object(DRIVER)->message(mess);
#endif
	if(type == "/logs/compile_errors.log" && this_user()){/* send on to user of note */
		this_user()->message(mess);
	}
}

/* add functions for sorting out logs and retrieving via different info,
   eventually the log will just log into an object */
