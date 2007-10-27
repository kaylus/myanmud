# include <kernel/kernel.h>
# include <kernel/user.h>
# include <type.h>

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
    string arg;

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
	call_other(this_object(), "cmd_" + str, user, str, arg);
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

    while(i--){
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
  	    catch(obj->move(user->query_body()));
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
    int *sizes, *times, long, ancient, i, j, sz, max, len, rows, time;

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
		str = ESC + "[34;1m" + str + "/" + ESC + "[0m";
	    } else if (objects[j]) {
		str = ESC + "[32;1m" + str + "*" + ESC + "[0m";
	    }
	    j += rows;
	    if (j >= sz) {
		dirlist += str + "\n";
		break;
	    }
	    dirlist += (str + "                                                    ")
		       [0 .. max];
	}
    }
    message(dirlist);
}

/*
 * dest: destructs an object in wizard's inventory or environ
 */



