/* The drop command. Lets a player pick up an object.
   Mobydick, 7-15-94
   Hymael - brought it in line
*/

#define SYNTAX "Usage: drop <item>\n"

int do_command (string str) {
    object thing;
    string res, type;
	int num;

    if (!str)
    	return fail_msg(SYNTAX);

	/***COINS***/
    if(sscanf(str, "%d %s coin", num, type) == 2 || sscanf(str, "%d %s", num, type) == 2){
		str = catch(TP->wealth_move(TP->query_environment(), type, num));
		if(!str){
			write("You drop "+num+" "+type+".\n");
			say(TPN+" drops "+num+" "+type+".\n");
			return 1;
		}
		return fail_msg(str);
	}
    /***END COINS***/
    thing = TP->present(str) ;
    if(!thing)
    	return fail_msg ("You don't possess "+article(str)+" "+str+".\n");

    res = catch(thing->move(TP->query_environment()));
    if(res){
        write("You can't bring yourself to drop it."+res+"\n") ;
		return 1;
    }
    str = thing->query_short();
    write("You drop the "+str+".\n") ;
    say(TPN+" drops "+str+".\n") ;
    return 1;
}

string help(){
	return SYNTAX+"\n\
This command allows you to drop the given item to the floor.";
}