/*
 * This is the help daemon, all requests for help
 * should be routed through this daemon
 */

#define HELP_DIR "/help/"
#define HELP_DIRS ({ HELP_DIR + "help/", HELP_DIR + "commands/" })
#define HELP_WIZ ({ HELP_DIR + "wiz/" })

mapping help; /* this mapping will contain help directories */

void create(varargs int clone){
    help = ([]);
    /* load it up */
    help["player"] = HELP_DIRS;
    help["wiz"] = HELP_WIZ;
}

string help(string topic){/* a request is made for help */
    string *dirs, str;
    int i;
    /* add in some dummy checking for ../ str? */
    if(sscanf(topic, "%*s..%*s") > 0){/* someone's being naughty? */
	LOGD->log("Faulty help " + topic + "\n " + this_user()->query_Name(), "helpd");
	return "No such topic.\n";
    }
    if(this_user()->query_wiztool()){/* check wiz commands */
	dirs = help["wiz"];
	for(i=sizeof(dirs);--i>=0;){
	    str = read_file(dirs[i]+topic);
	    if(str)
		return str;
	}
    }
    dirs = help["player"];
    for(i=sizeof(dirs);--i>=0;){
	str = read_file(dirs[i]+topic);
	if(str)
	    return str;
    }
    /* check more or return fail string */
    return "No such topic.\n";
}

