/*
	unwield da weapon
*/

#define SYNTAX "Usage: unwield <item>\n"

int do_command (string str) {

    object thing;
    string mess;
    int fun;

    if (!str) {
        return fail_msg(SYNTAX);
    }
    thing = TP->present(str);
    if (thing){
		if(!thing->is_weapon()) return fail_msg("You can't unwield that.\n");
		if((mess = TP->unwield(thing))){
			return fail_msg(mess);
		}
		catch(fun = call_other(thing, thing->query_unwield_func()));
		if(!fun){/* messages not handled */
			write("You unwield "+thing->query_weapon_name()+".\n");
			say(TPN+" unwields "+thing->query_weapon_name()+".\n");
		}
		return 1;
	}
	write("No "+str+" to unwield.\n");
	return 1;
}

string help(){
	return SYNTAX+"\n\
This command allows you to unwield a given weapon.";
}