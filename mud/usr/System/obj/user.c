# include <kernel/kernel.h>
# include <kernel/user.h>
# include <kernel/access.h>
# include <config.h>

inherit LIB_USER;
inherit user API_USER;
inherit access API_ACCESS;

# define STATE_NORMAL		0
# define STATE_LOGIN		1
# define STATE_OLDPASSWD	2
# define STATE_NEWPASSWD1	3
# define STATE_NEWPASSWD2	4
# define STATE_INPUTOBJ     5

# define USR_SAVE_DIR  "/usr/System/data"

static string name;		/* user name */
static string Name;		/* capitalized user name */
static mapping state;		/* state for a connection object */
#ifndef SYS_PERSISTENT
string password;		/* user password */
string body_name;       /* hackish */
#endif
static string newpasswd;	/* new password */
static object wiztool;		/* command handler */
static int nconn;		/* # of connections */
object body;            /* subjects body, some sort of saving mechanism */
static object input_to_obj;        /* input to object */

/*
 * NAME:	create()
 * DESCRIPTION:	initialize user object
 */
static void create(int clone)
{
    if(!find_object(SYSTEM_WIZTOOL)) compile_object(SYSTEM_WIZTOOL);
    if(!find_object(BODY)) compile_object(BODY);

    if (clone) {
	user::create();
	access::create();

	state = ([ ]);
    }
}

int is_user(){ return 1; }

static void set_this_player(object player) {
    find_object(BRAIND)->set_this_player(player);
}

/* get subject's body */
object query_body(){ return body; }

/* get cap name */
string query_Name(){ return Name; }

string query_name(){ return name; }

object query_wiztool(){ return wiztool; } /* hacked in for use to check if someone is a wiz */

void issue_wiztool(){ /* TODO: security? Should query_wiztool work broadly? */
    /*if(!wiztool && SYSTEM())*/
    wiztool = clone_object(SYSTEM_WIZTOOL, name);
    LOGD->log("Wiztool issued to "+name, "wizard");
}

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

void set_body(object obj){
    /*if(previous_program() != ACCOUNTD && !SYSTEM())error("Illegal call to set_body.\n");*/

    if(!obj->is_body())error("Object is not a body.\n");

    body = obj;
    ACCOUNTD->set_body(body);
    body->set_user(this_object());
}
#ifndef SYS_PERSISTENT
/* save function obsolesence*/
void _save(){
    string caught;
    if(!name || strlen(name) < 1){ error("Trying to save unnamed."); }

    LOGD->log("Saving " + name, "users");
    if(body)body_name = object_name(body);
    caught = catch(save_object(USR_SAVE_DIR + "/" + name + ".pwd"));
    if(caught)LOGD->log("Error in player save " + caught +"\n", "users");
}
/* restore me */
void _restore(){
    string caught;
    if(!name || strlen(name) < 1){ error("Trying to restore unnamed."); }

    LOGD->log("Restoring " + name, "users");
    caught = catch(restore_object(USR_SAVE_DIR + "/" + name + ".pwd"));
    if(body_name)body = find_object(body_name);

    if(caught)LOGD->log("Error in player restore " + caught +"\n", "users");
}
#endif
/*
 * NAME:	login()
 * DESCRIPTION:	login a new user
 */
int login(string str)
{

    if (previous_program() == LIB_CONN) {
	if (nconn == 0) {
	    ::login(str);
	}
	nconn++;
	if (strlen(str) == 0 || sscanf(str, "%*s ") != 0 ||
	  sscanf(str, "%*s/") != 0 ||
	  ACCOUNTD->is_banned(str)) {
	    return MODE_DISCONNECT;
	}
	name = lowercase(str);
	Name = capitalize(name);
	LOGD->log(Name+" logging in.", "users");
	#ifndef SYS_PERSISTENT
	_restore();
	#endif

	#ifdef SYS_PERSISTENT
	if (ACCOUNTD->password_exists(name)) {
	    #elif
	    if(password){
		#endif
		/* check password */
		previous_object()->message("Password:");
		state[previous_object()] = STATE_LOGIN;
	    } else {
		/* no password; switch to making one immediately */
		connection(previous_object());
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
    void logout(int quit){
	if (previous_program() == LIB_CONN && --nconn == 0 || previous_program() == "~System/initd") {
	    set_this_player(this_object());
	    #ifndef SYS_PERSISTENT
	    _save();
	    #endif
	    body->stasis();/* store body */

	    if (query_conn()) {
		if (quit) {/* TODO redo this messaging */
		    tell_audience(Name + " logs out.\n");
		} else {
		    tell_audience(Name + " disconnected.\n");
		}
	    }
	    ::logout();
	    ACCOUNTD->logout(this_object());
	    if (wiztool) {
		destruct_object(wiztool);
	    }
	    destruct_object(this_object());
	}
    }

    /*
     * NAME:        input_to()
     * DESCRIPTION: this is how to redirect an input to an object.  Only one redirect at a time
     *              The object should define a function input(), if it doesn't it is not a valid
     *              input_to object. Input will return 0 if it wants to be removed
     */
    void input_to(object obj){
	/* check if we already have an inputting object */
	if(input_to_obj || (wiztool && query_editor(wiztool))){
	    error("Already inputing to an object.\n");
	    return;
	}
	/* check for an input in given object */
	if(!function_object("input_to", obj)){
	    error("Ineligible input object.\n");
	    return;
	}
	input_to_obj = obj;
	state[query_conn()] = STATE_INPUTOBJ;/* turn input toward obj section */
	/* check for an init_input function, then call it */
	if(function_object("init_input", obj)){
	    obj->init_input();
	}
    }

    object _input_to(string str){/* internal call that handles input stuff to objects, returns input_to_obj, nil if we want to remove */
	object temp_obj;
	if(!input_to_obj)return nil;

	temp_obj = input_to_obj;
	input_to_obj = input_to_obj->input_to(str);

	if(!input_to_obj){/* inputs done */
	    if(function_object("input_done", temp_obj)){/* tie up function, optional */
		return (input_to_obj = temp_obj->input_done());/* function should return nil if done, or a new object */
	    }
	}

	return input_to_obj;
    }

    /*
     * NAME:	receive_message()
     * DESCRIPTION:	process a message from the user
     * TODO: aliasing system
     */
    int receive_message(string str)
    {
	if (previous_program() == LIB_CONN || previous_object() == wiztool) {/* is this || in error with the state setting? */
	    string cmd;
	    object user, *users;
	    int i, sz;

	    set_this_player(((body) ? (body) : (this_object())));
	    /* is this where we should redirect to game object input? */
	    switch (state[previous_object()]) {
	    case STATE_INPUTOBJ:
		if(input_to_obj){
		    input_to_obj = _input_to(str);
		    if(!input_to_obj){
			state[previous_object()] = STATE_NORMAL;
		    }
		    return MODE_ECHO;
		}else{
		    state[previous_object()] = STATE_NORMAL;
		}/* flow into state_normal */
	    case STATE_NORMAL:
		str = strip(str);/* strip leading and trailing spaces */
		cmd = str;
		if (strlen(str) != 0 && str[0] == '!') {
		    cmd = cmd[1 ..];
		}

		if (!wiztool || !query_editor(wiztool) || cmd != str) {
		    /* check input_to, add in work around ! */

		    /* check standard commands */
		    if (strlen(cmd) != 0) {
			switch (cmd[0]) {
			case '\'':
			    if (strlen(cmd) > 1) {
				cmd[0] = ' ';
				str = strip(cmd);
			    }
			    cmd = "say";
			    str = cmd+" "+str;
			    break;

			case ':':
			    if (strlen(cmd) > 1) {
				cmd[0] = ' ';
				str = strip(cmd);
			    }
			    cmd = "emote";
			    str = cmd+" "+str;
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
			    tell_audience(Name + " says, \"" + capitalize(str) + "\"\n");
			    message("You say, \"" + capitalize(str) +"\"\n");
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
			if (ACCOUNTD->password_exists(name)) {
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
		    } else if (strlen(str) != 0) {/* strip trailing spaces TODO*/
			message("No command: " + str + "\n");
		    }
		}
		break;

	    case STATE_LOGIN:
		if (!ACCOUNTD->password_check(str)) {
		    previous_object()->message("\nBad password.\n");
		    return MODE_DISCONNECT;
		}
		connection(previous_object());
		message("\n");
		LOGD->log(Name + " logs in.\n", "usage");

		if (!wiztool && 
		  #ifdef SYS_PERSISTENT
		  !ACCOUNTD->wiz_suspended(name) && ACCOUNTD->password_exists(name) &&/* only issue when there's pass */
		  #endif
		(name == "admin" || sizeof(query_users() & ({ name })) != 0)) {/* move this check to accountd? */
		    issue_wiztool();/* move this to a function in accountd? TODO make grant do this automatically with a wrapper */
		}
		/* get body from ACCOUNTD or make one */
		if(!body)body = ACCOUNTD->get_body(name);
		LOGD->log("accountd returned "+((body)?object_name(body):"none"), "accountd");
		if(!body || catch(body->awaken(this_object()))){
		    set_body(ACCOUNTD->create_body());
		    input_to(body);	  
		    return MODE_ECHO;
		} else {
		    state[previous_object()] = STATE_NORMAL;
		    body->move(ROOMD->query_start_room(), "");
		}
		break;

	    case STATE_OLDPASSWD:
		if (ACCOUNTD->password_check(str)) {
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
		    if(ACCOUNTD->password_exists(name))message("\nPassword changed.\n");
		    ACCOUNTD->set_password(str);
		} else {/* is this alright when a player logs in for the first time? */
		    message("\nMismatch; password not changed.\n");
		}
		newpasswd = nil;

		/* get body from ACCOUNTD or make one */
		if (!wiztool && 
		  #ifdef SYS_PERSISTENT
		  !ACCOUNTD->wiz_suspended(name) && ACCOUNTD->password_exists(name) &&/* only issue when there's pass */
		  #endif
		(name == "admin" || sizeof(query_users() & ({ name })) != 0)) {/* move this check to accountd? */
		    issue_wiztool();/* move this to a function in accountd? TODO make grant do this automatically with a wrapper */
		}
		if(!body)body = ACCOUNTD->get_body(name);
		LOGD->log("accountd returned "+((body)?object_name(body):"none"), "accountd");
		if(!body || catch(body->awaken(this_object()))){
		    set_body(ACCOUNTD->create_body());
		    input_to(body);	  
		    return MODE_ECHO;
		} 
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
    /* intercept and color, based on settings? */
    int message(string msg){
	msg = find_object(ANSID)->parse_pinkfish(msg);

	return ::message(msg);
    }

