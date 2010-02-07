/* the xa command - Hymael */
#define SYNTAX "Usage: xa <person>\n"

int do_command (string str) {
    object room, thing;
    string name;
    int res;

    if (!str){
		if(!(thing = TP->query_target())){
			return fail_msg(SYNTAX);
		}
	}
	if(!thing){
    	room = TP->query_environment();
    	if(!room) return fail_msg("Where are you?");

    	thing = room->present(str);
    	if (!thing) return fail_msg ("There is no "+str+" to xa.\n") ;
    	if(!thing->query_has_health()) return fail_msg("That is inanimate.\n");
	}
    name = thing->query_cap_name();
    write(name + thing->query_xa() + "\n");
    return 1 ;
}

string help(){
	return SYNTAX+"\n\
This command allows you to gauge the healthiness of an object.";
}