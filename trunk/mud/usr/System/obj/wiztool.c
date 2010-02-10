# include <kernel/kernel.h>
# include <kernel/user.h>
# include <kernel/access.h>
# include <type.h>
/* add wrapper classes for higher level kernel commands */
inherit LIB_WIZTOOL;


private object user;		/* associated user object */

/*
* NAME:	create()
* DESCRIPTION:	initialize object
*/
static void create(int clone)
{
    if (clone) {
	::create(200);
	user = this_user();
    }
}

/*
* NAME:	message()
* DESCRIPTION:	pass on a message to the user
*/
static void message(string str)
{
    user->message(str);
}

object query_user(){
    return user;
}
/*
* NAME:	input()
* DESCRIPTION:	deal with input from user
*/
void input(string str)
{
    if (previous_object() == user) {

	call_limited("process", str);
    }
}

/*
* NAME:	process()
* DESCRIPTION:	process user input
*/
static void process(string str)
{
    string arg, err;

    /* add in redirect to any object, sort of like editor? */
    if (query_editor(this_object())) {
	if (strlen(str) != 0 && str[0] == '!') {
	    str = str[1 ..];
	} else {
	    str = editor(str);
	    if (str) {
		message(str);
	    }
	    return;
	}
    }

    if (str == "") {
	return;
    }

    sscanf(str, "%s %s", str, arg);
    if (arg == "") {
	arg = nil;
    }

    switch (str) {
    case "code":
    case "history":
    case "clear":
    case "compile":
    case "clone":
    case "destruct":
    case "dest":

    case "cd":
    case "pwd":
    case "ls":
    case "cp":
    case "mv":
    case "rm":
    case "mkdir":
    case "rmdir":
    case "ed":

    case "access":
    case "grant":
    case "ungrant":
    case "quota":
    case "rsrc":

    case "people":
    case "status":
    case "swapout":
    case "statedump":
    case "shutdown":
    case "reboot":

    case "spectrum":
    case "summon":
    case "goto":
    case "call":
	call_other(this_object(), "cmd_" + str, user, str, arg);
	if(err)LOGD->log(str + " caused error in "+user->query_name()+": "+err, "wiztool");
	break;

    default:
	message("No command: " + str + "\n");
	break;
    }
}

/*
* NAME:	cmd_summon()
* DESCRIPTION:	summon player to you
*/
static void cmd_summon(object user, string cmd, string str)
{
    object player, *users; /* hackish for now */
    int i;

    if (!str) {
	message("Usage: " + cmd + " <player>\n");
	return;
    }

    str = str;/* lowercase */
    users = users();
    if(!(i = sizeof(users)))
	return;

    while(i--){/* code to use find_player() */
	if(users[i]->query_name() == str){
	    player = users[i]->query_body();
	    break;
	}
    }
    if(!player){
	message("No player named <"+capitalize(str)+">\n");
	return;
    }
    player->message(this_user()->query_Name()+" has summoned you!\n");
    player->move(this_user()->query_body()->query_environment(), "", 1);
    message("You summon " + player->query_Name()+".\n");
}
static void cmd_spectrum(object user, string cmd, string str)
{
    int i;
    string ret;

    ret = "Spectrum:\n";

    for(i=0; i<48; i++){
	ret += "\033["+i+"mcolor{"+i+"}\033[1m{bold}\033[0m\n";
    }
    message(ret);
}

/*
*  * NAME:	cmd_clone()
*   * DESCRIPTION:	clone an object, move it to cloners dir
*    */
static void cmd_clone(object user, string cmd, string str)
{
    mixed obj;

    obj = parse_obj(str);
    switch (typeof(obj)) {
    case T_INT:
	message("Usage: " + cmd + " <obj> | $<ident>\n");
    case T_NIL:
	return;

    case T_STRING:
	str = obj;
	obj = find_object(str);
	break;

    case T_OBJECT:
	str = object_name(obj);
	break;
    }

    if (sscanf(str, "%*s" + CLONABLE_SUBDIR + "%*s#") != 1) {
	message("Not a master object.\n");
    } else if (!obj) {
	message("No such object.\n");
    } else {
	str = catch(obj = clone_object(str));
	if (str) {
	    message(str + ".\n");
	} else if (obj) {
	    store(obj);
	    if(obj->is_object()){
			cmd = catch(obj->move(user->query_body()));
			if(cmd)
				message("Error: Object couldn't be moved - "+cmd+".\n");
		}
	}
    }
}

/*
* NAME:	cmd_ls() override of inherited
* DESCRIPTION:	list files
*/
static void cmd_ls(object user, string cmd, string str)
{
    mixed *files, *objects;
    string *names, timestr, dirlist, directory;
    int *sizes, *times, long, ancient, i, j, sz, max, len, rows, time, adjust;

    if (!str) {
	str = ".";
    } else if (sscanf(str, "-%s", str) != 0) {
	long = 1;
	if (str == "l") {
	    str = ".";
	} else if (sscanf(str, "l %s", str) == 0) {
	    message("Usage: " + cmd + " [-l] [<file> ...]\n");
	    return;
	}
    }

    directory = query_directory();

    files = expand(str, 1, FALSE);	/* must exist, short file names */

    if (files[4] == 1 && sizeof(files[0]) == 1 && files[1][0] == -2) {
	str = files[0][0];
	if (str[0] != '/') {
	    str = directory + "/" + str;
	}
	files = get_dir(str + "/*");
	if (!files) {
	    message(str + ": Access denied.\n");
	    return;
	}
    }

    names = files[0];
    sz = sizeof(names);
    if (sz == 0) {
	return;
    }
    sizes = files[1];
    times = files[2];
    objects = files[3];

    for (i = 0; i < sz; i++) {
	j = strlen(names[i]);
	if (j > max) {
	    max = j;
	}
	j = sizes[i];
	if (j > len) {
	    len = j;
	}
    }
    if (long) {
	len = strlen((string) len) + 1 + 11;/* Hymael added some for colors */
	max += len + 14;
	ancient = time() - 6 * 30 * 24 * 60 * 60;
    }

    max += 2;
    j = (79 + 2) / (max + 1);
    if (j == 0) {
	rows = sz;
    } else {
	rows = (sz + j - 1) / j;
    }

    dirlist = "";
    for (i = 0; i < rows; i++) {
	j = i;
	for (;;) {
	    if (long) {
		str = "                        ";
		if (sizes[j] >= 0) {
		    str += (string) sizes[j];
		}

		time = times[j];
		timestr = ctime(time);
		if (time >= ancient) {
		    timestr = timestr[3 .. 15];
		} else {
		    timestr = timestr[3 .. 10] + timestr[19 .. 23];
		}
		str = str[strlen(str) - len ..] + timestr + " " + names[j];
	    } else {
		str = names[j];
	    }

	    if (sizes[j] < 0) {
		str = "%^BOLD%^%^BLUE%^" + str + "/%^RESET%^";
		adjust = 25;
	    } else if (objects[j]) {
		str = "%^BOLD%^%^GREEN%^" + str + "*%^RESET%^";
		adjust = 26;
	    } else {
		adjust = 0;
	    }
	    j += rows;
	    if (j >= sz) {
		dirlist += str + "\n";
		break;
	    }
	    dirlist += (str + "                                                    ")
	    [0 .. (max + adjust)];
	}
    }
    message(dirlist);
}

/*
* dest: destructs an object in wizard's inventory or environ
*/
static void cmd_dest(object user, string cmd, string str){
    mixed thing;
    int i;

    if(!str || !strlen(str)){
	message("Usage: dest <object>\n");
	return;
    }
    /* add in check for $num functionality */
    if (sscanf(str, "$%d", i) && (thing = parse_obj(str))){
	message("You destruct : "+thing->query_short()+".\n");/* may have to make query_short more elaborate */
	destruct_object(thing);
	return;
    }

    /* check inventory */
    if(thing = user->query_body()->present(str)){
	message("You destruct : "+thing->query_short()+".\n");
	user->query_body()->query_environment()->message(user->query_Name()+" dests: "+thing->query_short()+"\n", ({user->query_body()}));
	destruct_object(thing);
	return;
    }

    /* check environment */
    if(thing = user->query_body()->query_environment()->present(str)){
	message("You destruct : "+thing->query_short()+".\n");
	user->query_body()->query_environment()->message(user->query_Name()+" dests: "+thing->query_short()+"\n", ({user->query_body()}));
	destruct_object(thing);
	return;
    }
    message("No "+str +" to dest.\n");
}

/*
* more: pager for a file, make wiztool input_to_obj?
*/

/*
* home: returns you to your workroom
*/

/*
* goto: trans you to the named room, or player
*/

static void cmd_goto(object user, string cmd, string str){
    mixed thing;
    int i;

    if(!str || !strlen(str)){
	message("Usage: goto <object/room>\n");
	return;
    }
    /* add in check for $num functionality */
    if (sscanf(str, "$%d", i) && (thing = parse_obj(str))){
	if(thing <- "/usr/System/obj/room"){/* suitable destination */
	    user->query_body()->move(thing, "", 1);
	    message("You move to " + thing->query_short() + ".\n");
	    return;
	}
    }else{
	thing = find_player(thing);
	if(thing && thing->is_player()){
	    user->query_body()->move(thing->query_environment(), "", 1);
	    message("You move to " + thing->query_Name() + "'s room.\n");
	    thing->message(this_player()->query_Name() + " appears in your room.\n");
	    /* add message to others */
	    return;
	}
	/* add in instance of file */

    }
    message("Not a suitable destination.\n");/* may have to make query_short more elaborate */
    return;
    message("No "+str +" to dest.\n");
}

/*
* invis: turns you invis, requires the coding of a query_vision
*/

/*
* tail: prints the last bit of a file
*/

/*
* gauge: calculates the given ticks/time of the given command
*/

/*
* force: forces a body to do a command
*/

/*
* nuke: destroys a given player/wiz
*/

/*
* wall: realm echo
*/

/*
* NAME:	cmd_summon()
* DESCRIPTION:	summon player to you
*/
static void cmd_newcommand(object user, string cmd, string str)
{


    message("This is a dummy command.\n");
}

/* return array with ({ mixed value, TYPE }) ? */ 
mixed parse_call(string str){/* TODO: trouble materializing mappings and such */
    string parsed;
    mixed ret;
    int i;
    float x;

    str = strip(str);
    str = strip(str, '"');
    if(str == "me")return ({ user->query_body(), T_OBJECT });

    if(str == "here")return ({ user->query_body()->query_environment(), T_OBJECT });

    if(sscanf(str, "$%d", i))return ({ fetch(i), T_OBJECT });

    /* check for data */
    if(!catch(i=(int)str))return ({ i, T_INT });
    if(!catch(x=(float)str))return ({ x, T_FLOAT });

    if(sscanf(str, "#%d", i) || sscanf(str, "/%s", parsed)){/* treat as file, unless nil */
	ret = ({ find_object(str), T_OBJECT });
    }
	
	if(find_player(str))
		return ({ find_player(str), T_OBJECT });
	
    /* default to string */
    if(!ret || ret[0] == nil)
	return ({ str, T_STRING });

    return ret;
}

/*
* cmd_call
* wiz can call an object or himself and execute a functionality
*/

static void cmd_call(object user, string cmd, string str){
    string id, function, args, *calls;
    mixed ret, obj, obj2;

    if(!str || !strlen(str) || !sizeof(calls = explode(str, ";"))){
	message("Usage: call <object $/here/name of player/me>;function(;argument)\n");
	return;
    }
    /* TODO: strip leading and ending spaces */
    /* calls populated by ; exploded array */
    switch(sizeof(calls)){
    case 1:/* just have one object to deal with, just store it in history */
	store(parse_call(calls[0])[0]);/* need more elaborate? */
	return;
    case 2:/* we have form call obj;function */
	/* load up call[0] */
	obj = parse_call(calls[0]);
	if(obj[1] != T_OBJECT){
	    message("Invalid object.\n");
	    return;
	}

	if(catch(function = (string)strip(strip(calls[1]), '"'))){
	    message("Function not string.\n");
	    return;
	}	
	if(!function_object(function, (object)obj[0])){
	    message("No function: \""+function+"\" in object.\n");
	    return;
	}
	str = catch(ret = call_other((object)obj[0], function));
	if(str){
	    message("Error: "+str);
	    return;
	}
	if(ret)
	    store(ret);

	return;

    case 3:/* we have form obj;function;arg */
	/* load up call[0] */
	obj = parse_call(calls[0]);
	if(obj[1] != T_OBJECT){
	    message("Invalid object.\n");
	    return;
	}

	if(catch(function = (string)strip(strip(calls[1]), '"'))){
	    message("Function not string.\n");
	    return;
	}	

	if(!function_object(function, (object)obj[0])){
	    message("No function: \""+function+"\"in object.\n");
	    return;
	}
	obj2 = parse_call(calls[2]);
	switch(obj2[1]){
	case T_OBJECT:
	    str = catch(ret = call_other((object)obj[0], function, (object)obj2[0]));
	    break;
	case T_INT:
	    str = catch(ret = call_other((object)obj[0], function, (int)obj2[0]));
	    break;
	case T_FLOAT:
	    str = catch(ret = call_other((object)obj[0], function, (float)obj2[0]));
	    break;
	case T_STRING:
	    str = catch(ret = call_other((object)obj[0], function, (string)obj2[0]));
	    break;
	default:
	    str = catch(ret = call_other((object)obj[0], function, obj2[0]));

	}
	if(str){
	    message("Error: "+str);
	    return;
	}
	if(ret)
	    store(ret);

	return;
    }
    message("Usage: call <object $/here/name of player/me>;function(;argument)\n");
}
