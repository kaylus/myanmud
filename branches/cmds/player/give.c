/* The give command. Lets a player give an object to another.
   Mobydick, 7-16-94
*/

#define SYNTAX "Usage: give <item> to <player>\n"

int do_command (string str) {
    object thing, target, env ;
    string name, item;
    string res;

    if(!str || sscanf(str,"%s to %s",item,name) != 2)
    	return fail_msg(SYNTAX);

    thing = TP->present(item) ;
    if(!thing)
        return fail_msg("You don't have a "+item+" to give away.\n");

    env = TP->query_environment();
    target = env->present(name);
    if(!target || !target->query_living())
		return fail_msg("There is no one named "+capitalize(name)+" to give it to.\n");

    res = catch(thing->move(target));

    if(res){
		write (capitalize(name)+" cannot carry it.\n") ;
		return 1 ;
    }
    str = thing->query_short();
    write ("You give "+str+" to "+capitalize(name)+".\n") ;
    name = previous_object()->query_cap_name() ;
    target->catch_tell(name+" gives you "+str+".\n") ;
    say (name+" gives "+target->query_cap_name()+" "+str+".\n",
		({ target }) ) ;
    return 1;
}

string help(){
	return SYNTAX+"\n\
This command allows you to hand a given item to a player\n\
in your current room.";
}