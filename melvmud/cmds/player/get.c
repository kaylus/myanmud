/* The get command. Lets a player pick up an object.
   "get all" is not yet supported. Getting items from containers should
   probably be defined in container.c and not here.
   Mobydick, 7-15-94
*/

#define SYNTAX "Usage: get all | <item> [from <container>]\n"

int do_command (string str) {
    object thing, env;
    string s1, s2;
    int num;

    string res;

    if (!str || sscanf(str, "%s from %s", s1, s2) == 2)
    	return fail_msg(SYNTAX);

    env = TP->query_environment() ;
    if(!env) return fail_msg("No environment.\n");

    if(str == "all"){/* get everything */
    	int sz, i;
    	object *things;

		things = env->query_inventory();
		if(!things || !(sz=sizeof(things))){
			write("Nothing to get.\n");
			return 1;
		}
		while(sz--){
			if(things[sz]->query_living() || things[sz]->prevent_get())
				continue;

			i++;
			res = catch(things[sz]->move(TP));
			if(res){
				/* nothing for now */
			}
		}
		if(i){
			write("You get everything.\n");
		}else{
			write("Nothing to take.\n");
		}
		return 1;
	}
	/***MONEY***/
	if(sscanf(str, "%d %s", num, s1) == 2 || sscanf(str, "%d %s coin", num, s1) == 2){
		string type;
		thing = env->present(s1);
		if(!thing || !thing->is_coins())
			return fail_msg("No money.\n");

		type = thing->query_cointype();
		str = catch(thing->coin_move(TP, num));
		if(!str){
			write("You get "+num+" "+type+" coin"+( (num > 1) ? "s" : "" )+".\n");
			say(TPN+" gets some money.\n");
			return 1;
		}
		return fail_msg(str);
	}

    thing = env->present(str) ;
    if(!thing)
    	return fail_msg("No "+str+" to get.\n");

/* Check to see if the item is willing to be picked up. */
    if (thing->prevent_get()) {
		write ("You cannot pick that up.\n") ;
		return 1;
    }
    res = catch(thing->move(TP));
    if (res) {
        write ("You can't pick it up."+res+"\n") ;
		return 1 ;
    }
    str = thing->query_short();
    write("You get the "+str+".\n") ;
    say(TPN+" takes "+str+".\n") ;
    return 1 ;
}

string help(){
	return SYNTAX+"\n\
This command attempts to pick up the given item in your room.\n\
Or if the form get X from Y is used, you attempt to get X from\n\
container Y.";
}