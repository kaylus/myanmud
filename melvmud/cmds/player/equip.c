/********************************
 * equip a given piece of armor *
 ********************************/
#define SYNTAX "Usage: equip <item>\n"

int do_command (string str) {

    object thing, target, env ;
    string name, mess;
    int fun, res ;

    if (!str) {
        return fail_msg(SYNTAX);
    }
    thing = TP->present(str);
    if (thing){
		if(!thing->is_armor())return fail_msg("You can't equip that.\n");
		/*if(TP->query_worn(thing))return fail_msg("You're already wearing that.\n");*/
		if((mess = TP->equip_armor(thing)) != nil){
			/*if(thing->query_type() != "shield"){
				write("You're already equipping something of that nature.\n");
			}else{
				write("You haven't a free hand to equip that.\n");
			}
			return 1;*/
			return fail_msg(mess);
		} else {
			catch(fun = call_other(thing, thing->query_equip_func()));
			if(!fun){/* messages not handled */
				write("You equip "+thing->query_short()+".\n");
				say(TPN+" equips "+thing->query_short()+".\n");
			}
			return 1;
		}
	}
	write("No "+str+" to equip.\n");
	return 1;
}

string help(){
	return SYNTAX+"\n\
This command allows you to equip a given item.";
}