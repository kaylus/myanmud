/**********************************
 * unequip a given piece of armor *
 **********************************/
#define SYNTAX "Usage: unequip <item>\n"

int do_command (string str) {
    object thing;
    string name, mess;
    int res, fun;

    if (!str) {
        return fail_msg(SYNTAX);
    }
    thing = TP->present(str);
    if (thing){
		/*if(!thing->is_armor())return fail_msg("That isn't armor.\n");*/
		if((mess = TP->unequip_armor(thing)) != nil){
			/*write("You aren't wearing the "+str+".\n");*/
			return fail_msg(mess);
		} else {
			catch(fun = call_other(thing, thing->query_unequip_func()));
			if(!fun){/* messages not handled */
				write("You unequip "+thing->query_short()+".\n");
				say(TPN+" unequips "+thing->query_short()+".\n");
			}
			return 1;
		}
	}
	write("You aren't wearing the "+str+".\n");
	return 1;
}

string help(){
	return SYNTAX+"\n\
This command allows you to unequip a given item.";
}