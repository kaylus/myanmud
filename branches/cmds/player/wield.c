/*
	wield da weapon
*/

#define SYNTAX "Usage: wield <item>\n"

int do_command (string str) {

    object thing, target, env ;
    string name, short, mess;
    int res, fun ;

    if (!str) {
        return fail_msg(SYNTAX);
    }
    thing = TP->present(str);
    if (thing){
		if(!thing->is_weapon())return fail_msg("You can't wield that.\n");
		if(TP->query_wielded(thing))return fail_msg("You're already wielding that.\n");

		if((mess = TP->wield(thing))){
			return fail_msg(mess);
		}
		/*switch(TP->wield(thing)){
		case -2: 	write("Your shield interferes.\n");
					return 1;
		case -1:	write("You need two hands for this large weapon.\n");
					return 1;
		case 0:		write("You haven't the hands to wield this weapon.\n");
					return 1;
		default:*/
		catch(fun = call_other(thing, thing->query_wield_func()));
		if(!fun){/* messages not handled */
			write("You wield "+thing->query_short()+".\n");
			say(TPN+" wields "+thing->query_short()+".\n");
		}
		return 1;
	}
	write("No "+str+" to wield.\n");
	return 1;
}

string help(){
	return SYNTAX+"\n\
This command allows you to wield a given weapon.";
}