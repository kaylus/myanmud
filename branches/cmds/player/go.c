/* The go command
	Hymael
*/

#define SYNTAX "Usage: go <dir>\n"

int do_command(string str){
    mapping exits;

    if(!str)
    	return fail_msg(SYNTAX);

    exits = TP->query_environment()->query_exits() ;
    if(!exits || !exits[str])
   		return fail_msg("You find no such exit.\n");

    str = catch(TP->move(exits[str], str));
    if(str)
		write("You make no headway.\n");

    return 1;
}

string help(){
	return SYNTAX+"\n\n\
This command allows you to move in a given direction.\n\n";
}
