# include <kernel/kernel.h>
# include <kernel/user.h>
# include <kernel/access.h>
# include <config.h>

inherit LIB_USER;
inherit user API_USER;
inherit access API_ACCESS;
inherit alias "/usr/System/lib/alias"; /* alias toolbox */


# define STATE_NORMAL		0
# define STATE_LOGIN		1
# define STATE_OLDPASSWD	2
# define STATE_NEWPASSWD1	3
# define STATE_NEWPASSWD2	4

# define USR_SAVE_DIR  "/usr/System/data"

static string name;		/* user name */
static string Name;		/* capitalized user name */
static mapping state;		/* state for a connection object */
string password;		/* user password */
static string newpasswd;	/* new password */
static object wiztool;		/* command handler */
static int nconn;		/* # of connections */
static int accinit;		/* access interface initialized */
object body;            /* subjects body, some sort of saving mechanism */
string body_name;       /* hackish */

/*
 * NAME:	create()
 * DESCRIPTION:	initialize user object
 */
static void create(varargs int clone)
{
    if(!find_object(SYSTEM_WIZTOOL)) compile_object(SYSTEM_WIZTOOL);
    if(!find_object(BODY)) compile_object(BODY);

    if (clone) {
	user::create();
	access::create();
	alias::create();

	accinit = TRUE;
	state = ([ ]);
	/*if(!body) body = clone_object(BODY);/* find body in storage? */
    }
}

/* get subject's body */
object query_body(){ return body; }

/* get cap name */
string query_Name(){ return Name; }

string query_name(){ return name; }

object query_wiztool(){ return wiztool; } /* hacked in for use to check if someone is a wiz */

/*
 * NAME:	tell_audience()
 * DESCRIPTION:	send message to listening users
 */
private void tell_audience(string str)
{
    object *users, user;
    int i;

    users = users();
    for (i = sizeof(users); --i >= 0; ) {
	user = users[i];
	if (user != this_object() &&
	  sscanf(object_name(user), SYSTEM_USER + "#%*d") != 0) {
	    user->message(str);
	}
    }
}
/* create body */
object create_body(){
	return clone_object(BODY);
}

void set_body(object obj){
	if(!obj->is_body())error("Object is not a body.\n");

	body = obj;
}

/*
 * NAME:	login()
 * DESCRIPTION:	login a new user
 */
int login(string str)
{
    int found_user;

    if (previous_program() == LIB_CONN) {
	if (nconn == 0) {
	    ::login(str);
	}
	nconn++;
	if (strlen(str) == 0 || sscanf(str, "%*s ") != 0 ||
	  sscanf(str, "%*s/") != 0) {
	    return MODE_DISCONNECT;
	}
	name = lowercase(str);
	Name = capitalize(name);

	found_user = restore_object(USR_SAVE_DIR + "/" + str + ".pwd");
	body = (body_name)?find_object(body_name):body; /* request body from userd? */
	/* check for stored body, remove from storage? */
	if(!body || !body->awaken()){
	    object room;

	    set_body(create_body());
	    body->move(ROOMD->query_start_room(), "");
	}

	if (password) {
	    /* check password */
	    previous_object()->message("Password:");
	    state[previous_object()] = STATE_LOGIN;
	} else {
	    /* no password; login immediately */
	    connection(previous_object());
	    tell_audience(Name + " logs in.\n");
	    if (!accinit) {
		access::create();
		accinit = TRUE;
	    }
	    if (str != "admin" && sizeof(query_users() & ({ str })) == 0) {
		message("> ");
		state[previous_object()] = STATE_NORMAL;
		return MODE_ECHO;
	    }
	    if (!wiztool) {
		wiztool = clone_object(SYSTEM_WIZTOOL, str);
	    }
	    message("Pick a new password:");
	    state[previous_object()] = STATE_NEWPASSWD1;
	}
	return MODE_NOECHO;
    }
}

/*
 * NAME:	logout()
 * DESCRIPTION:	logout user
 */
void logout(int quit)
{
    if (previous_program() == LIB_CONN && --nconn == 0) {
	body_name = object_name(body);

	save_object(USR_SAVE_DIR + "/" + name + ".pwd");

	body->stasis();/* store body */

	if (query_conn()) {
	    if (quit) {
		tell_audience(Name + " logs out.\n");
	    } else {
		tell_audience(Name + " disconnected.\n");
	    }
	}
	::logout();
	if (wiztool) {
	    destruct_object(wiztool);
	}
	destruct_object(this_object());
    }
}

/*
 * NAME:	receive_message()
 * DESCRIPTION:	process a message from the user
 * TODO: aliasing system
 */
int receive_message(string str)
{
    if (previous_program() == LIB_CONN) {
	string cmd;
	object user, *users;
	int i, sz;

	/* is this where we should redirect to game object input? */
	switch (state[previous_object()]) {
	case STATE_NORMAL:
	    cmd = str;
	    if (strlen(str) != 0 && str[0] == '!') {
		cmd = cmd[1 ..];
	    }

	    if (!wiztool || !query_editor(wiztool) || cmd != str) {
		/* check standard commands */
		if (strlen(cmd) != 0) {
		    switch (cmd[0]) {
		    case '\'':
			if (strlen(cmd) > 1) {
			    cmd[0] = ' ';
			    str = cmd;
			}
			cmd = "say";
			break;

		    case ':':
			if (strlen(cmd) > 1) {
			    cmd[0] = ' ';
			    str = cmd;
			}
			cmd = "emote";
			break;

		    default:
			sscanf(cmd, "%s ", cmd);
			break;
		    }
		}

		switch (cmd) {
		case "say":
		    if (sscanf(str, "%*s %s", str) == 0) {
			message("Usage: say <text>\n");
		    } else {
			tell_audience(Name + " says, \"" + str + "\"\n");
			message("You say, \"" + str +"\"\n");
		    }
		    str = nil;
		    break;

		case "emote":
		    if (sscanf(str, "%*s %s", str) == 0) {
			message("Usage: emote <text>\n");
		    } else {
			tell_audience(Name + " " + str + ".\n");
			message(Name + " " + str + ".\n");
		    }
		    str = nil;
		    break;

		case "tell":
		    if (sscanf(str, "%*s %s %s", cmd, str) != 3 ||
		      !(user=find_user(cmd))) {
			message("Usage: tell <user> <text>\n");
		    } else {
			user->message(Name + " tells you, \"" + str + "\"\n");
			message("You tell " + user->query_Name() + ", \"" + str + "\"\n");
		    }
		    str = nil;
		    break;

		case "users":
		case "who":
		    users = users();
		    str = "Logged on:";
		    for (i = 0, sz = sizeof(users); i < sz; i++) {
			cmd = users[i]->query_name();
			if (cmd) {
			    str += " " + cmd;
			}
		    }
		    message(str + "\n");
		    str = nil;
		    break;

		case "help":/* find player help files, change this over to helpd */
		    if(sscanf(str, "%*s/%*s") > 0 || sscanf(str, "%*s..%*s") > 0){
			message("Usage: help <topic>\n");
		    }else{
			if (sscanf(str, "%*s %s", str) == 0)/* default help */
			    str = "help";

			cmd = HELPD->help(str);

			if(!cmd){
			    message("No help on that subject.\n");
			}else{
			    message("******" + str + "******\n" + cmd + "\n");/* banner */
			}
		    }
		    str = nil;
		    break;

		case "password":
		    if (password) {
			message("Old password:");
			state[previous_object()] = STATE_OLDPASSWD;
		    } else {
			message("New password:");
			state[previous_object()] = STATE_NEWPASSWD1;
		    }
		    return MODE_NOECHO;

		case "quit":
		    return MODE_DISCONNECT;
		}
	    }

	    if (str) {
		if (body){
		    if(body->input(str))
			break; /* receive fail message, or nil for success */
		}/* check commands in other bins? (room, inventory, etc.)*/

		if (wiztool) {
		    wiztool->input(str);
		} else if (strlen(str) != 0) {
		    message("No command: " + str + "\n");
		}
	    }
	    break;

	case STATE_LOGIN:
	    if (crypt(str, password) != password) {
		previous_object()->message("\nBad password.\n");
		return MODE_DISCONNECT;
	    }
	    connection(previous_object());
	    message("\n");
	    tell_audience(Name + " logs in.\n");
	    if (!accinit) {
		access::create();
		accinit = TRUE;
	    }
	    if (!wiztool &&
	    (name == "admin" || sizeof(query_users() & ({ name })) != 0)) {
		wiztool = clone_object(SYSTEM_WIZTOOL, name);
	    }
	    break;

	case STATE_OLDPASSWD:
	    if (crypt(str, password) != password) {
		message("\nBad password.\n");
		break;
	    }
	    message("\nNew password:");
	    state[previous_object()] = STATE_NEWPASSWD1;
	    return MODE_NOECHO;

	case STATE_NEWPASSWD1:
	    newpasswd = str;
	    message("\nRetype new password:");
	    state[previous_object()] = STATE_NEWPASSWD2;
	    return MODE_NOECHO;

	case STATE_NEWPASSWD2:
	    if (newpasswd == str) {
		password = crypt(str);
		/* Hymael testing out player saves */
		/*if (wiztool) {*/
		/* save wizards only */
		save_object(USR_SAVE_DIR + "/" + name + ".pwd");
		/*}*/
		message("\nPassword changed.\n");
	    } else {
		message("\nMismatch; password not changed.\n");
	    }
	    newpasswd = nil;
	    break;
	}

	str = (wiztool) ? query_editor(wiztool) : nil;
	if (str) {
	    message((str == "insert") ? "*\b" : ":");
	} else {
	    message((name == "admin") ? "# " : "> ");
	}
	state[previous_object()] = STATE_NORMAL;
	return MODE_ECHO;
    }
}

