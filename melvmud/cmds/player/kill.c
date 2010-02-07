/* The kill - Hymael */
#define SYNTAX "Usage: kill <person>\n"

int do_command(string str){
    object room, thing;
    string name, tname;

    if(!str)
    	return fail_msg(SYNTAX);

    room = TP->query_environment();
    if(!room)
    	return fail_msg("Where are you?");

    thing = room->present(str);
    if(!thing)
    	return fail_msg("There is no "+str+" to attack.\n");

    if(!thing->query_is_attackable())
    	return fail_msg("You cannot attack that.\n");

    if(thing == TP)
    	return fail_msg("You masochist.\n");

	tname = thing->query_cap_name();
	name = TPN;
    switch(TP->attack(thing)){
	case 1:
		name = TPN;
		write("You attack "+tname+"!\n");
		say(name+" attacks "+tname+"!\n", ({ TP, thing }));
		thing->catch_tell(name+" attacks you!\n");
		break;
	default:
		write("You redouble your efforts against "+tname+".\n");
		break;
	}
    return 1;
}

string help(){
	return SYNTAX+"\n\
This command allows you to attack things.";
}