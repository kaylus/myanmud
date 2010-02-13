/*
 *  accountd
 * this handles player bodies and player info that is available through finger
 * TODO: need to store account data in lwo
 * TODO: suspension abilities, even suspension of wizzes, so they don't get wiztool's issued
 * TODO: ip bans, body issuing, pruning unused accounts/bodies
 * requires persistence, we'll enable based on SYS_PERSITENT
 * Q: should we leave user objects around to contain data like backlogs, colorsets?
 * Q: is query_name() trustworthy enough?
 */
# include <config.h>
# include <kernel/kernel.h>
# include <kernel/access.h>
# include <kernel/user.h>
# include <kernel/rsrc.h>

inherit access  API_ACCESS;
inherit rsrc	API_RSRC;
inherit user	API_USER;

object *bodies; /* holds all bodies that check in through the body's create */
mapping accounts; /* holds user name index mapping into player data, each data set is itself a mapping */
string *banned_names; /* names banned from play */

void create(){
    bodies = ({ });
    banned_names = ({ });
    accounts = ([ ]);
    
    access::create();
	rsrc::create();
	user::create();
}

int is_banned(string str){/* can also check for other facets of the name to make sure it complies */
    if(sizeof(banned_names & ({ str })))return 1;
    
    return 0;/* valid name */
}

void suspend_wiz(string name){
    object wiztool;
    if(!accounts[name])error("No person by that name.\n");
    
    accounts[name]["wiz_suspend"] = 1;
    if(accounts[name]["body"] && (wiztool = accounts[name]["body"]->query_user()->query_wiztool())){
	destruct_object(wiztool);
	accounts[name]["body"]->message("Your wizardly privileges have been suspended.\n");
    }
}

void unsuspend_wiz(string name){
    object user;
    if(!accounts[name])error("No person by that name.\n");
    
    /*if(name != "admin" && !sizeof(query_users() & ({ name })))error("Person isn't a wizard.\n");*/
    
    if(!accounts[name]["body"])error("No body.\n");
    
    user = accounts[name]["body"]->query_user();
    accounts[name]["wiz_suspend"] = 0;
    if(!user->query_wiztool()){
	user->issue_wiztool();
	user->message("Your wizardly privileges have been reinstated.\n");
    }
}

string *get_users(){ return query_users(); }
/* create body */
object create_body(){
    return clone_object(BODY);
}

void add_body(object BODY body){
    if(sizeof(bodies & ({ body })))return;/* already in array */
    bodies += ({ body });
}

void set_body(object obj){
    string name;
    
    /*if(!SYSTEM() || !KERNEL())error("Illegal set body call.\n");*/
    
    name = previous_object()->query_name();
    accounts[name]["body"] = obj;
}

object get_body(string name){
    if(accounts[name]["body"])return accounts[name]["body"];
    
    return nil;
}

/* TODO security measures */
object *query_bodies(){
    /*if(!SYSTEM())return nil;*/
    
    return bodies;
}

/* return finger data on individual TODO: security measures */
string finger(string str){
	string ret;
	
	if(!accounts[str])return "User does not exist.\n";
	
	ret = capitalize(str)+"\n";
	if(str == "admin" || sizeof(query_users() & ({ str })))ret += "Wizard\n";
	if(accounts[str]["last_on"])ret += "Last on: "+accounts[str]["last_on"]+"\n";
	if(accounts[str]["body"]){
		ret += accounts[str]["body"]->query_gender()+" "+accounts[str]["body"]->query_race();
	}
    return ret+"\n";
}

int password_exists(string user){
    if(accounts[user] && accounts[user]["password"])return 1;
    
    return 0; /* haven't passworded this account yet */
}

private void add_ip_fail(object user){
    string ip, ip_name, name;
    
	name = user->query_name();
    ip = user->get_ip_number();
    ip_name = user->get_ip_name();
    
    /* load up data */
    if(!accounts[name]["failed_ip"])accounts[name]["failed_ip"] = ([]);
    if(!accounts[name]["failed_ip_name"])accounts[name]["failed_ip_name"] = ([]);
    
    if(accounts[name]["failed_ip"][ip])accounts[name]["failed_ip"][ip]++;
    else                               accounts[name]["failed_ip"][ip] = 1;
    
    if(accounts[name]["failed_ip_name"][ip_name])accounts[name]["failed_ip_name"][ip_name]++;
    else                               accounts[name]["failed_ip_name"][ip_name] = 1;
    
    if(!accounts[name]["failed_login_time"])accounts[name]["failed_login_time"] = ([]);
    accounts[name]["failed_login_time"][ip] = time();/* log failed time */
}


private void add_ip_succeed(object user){
    string ip, ip_name, name, err;
    
	name = user->query_name();
    ip = user->get_ip_number();
    ip_name = user->get_ip_name();
	
    /* load up data */
    if(!accounts[name]["succeed_ip"])accounts[name]["succeed_ip"] = ([]);
    if(!accounts[name]["succeed_ip_name"])accounts[name]["succeed_ip_name"] = ([]);
    
    if(accounts[name]["succeed_ip"][ip])accounts[name]["succeed_ip"][ip]++;
    else                               accounts[name]["succeed_ip"][ip] = 1;
    
    if(accounts[name]["succeed_ip_name"][ip_name])accounts[name]["succeed_ip_name"][ip_name]++;
    else                               accounts[name]["succeed_ip_name"][ip_name] = 1;
    
    if(!accounts[name]["succeed_login_time"])accounts[name]["succeed_login_time"] = ([]);
    accounts[name]["succeed_login_time"][ip] = time();/* log succeed time */
    accounts[name]["last_login"] = time();
}

void set_password(string pass){
    string name;
    /*if(!SYSTEM() || !KERNEL())error("Illegal password set call.\n");*/
    name = previous_object()->query_name();/* security on this? */
    if(!accounts[name]){/* new account */
		accounts[name] = ([]);
		accounts[name]["created"] = time();
		add_ip_succeed(previous_object());
	}
    
    accounts[name]["password"] = hash_string("crypt", pass);
    accounts[name]["last_pass_change"] = time();
}

int password_check(string str){
    string user;
    
    user = previous_object()->query_name();
    if(!user /*|| !SYSTEM()*/)return 0;
    
    if(hash_string("crypt", str, accounts[user]["password"]) != accounts[user]["password"]){
	add_ip_fail(previous_object());
	return 0;
    }
    add_ip_succeed(previous_object());
    return 1; /* check succeeded */
}
/* should this also make sure the body object doesn't come back in wiz territory? or with wiz objects on it? */
int wiz_suspended(string str){/* this queries whether a wiz is suspended from receiving a wiztool */
    if(accounts[str]["wiz_suspend"])return 1;
    
    return 0;
}

void logout(object user){
    string name;
    /*if(!SYSTEM() || !KERNEL())error("Illegal call to logout.\n");*/
    
    name = user->query_name();
    accounts[name]["last_on"] = time();
}

mapping query_accounts(){ return accounts; }
