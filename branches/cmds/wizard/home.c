/* The home command.
   Hymael - using goto as template
   Mobydick, 5-28-94.
*/

#include <config.h>

#define SYNTAX "Usage: home\n"

int do_command(string str){
    str = resolve_path("~"+TPn+"/workroom.c");
    if(file_exists(str)){
		write("You proceed to your cozy home.\n");
		say(TPN+" clicks heels and is transported away.\n");
		str = (catch(TP->move(str)));
		if(str)
			write(str);

	} else {
		write("Make yourself a workroom.\n");
	}
    return 1 ;
}

string help(){
	return SYNTAX+"\n\
This command allows wizards to translocate to their workrooms.\n\
For this command to work, a wizard must have workroom.c in their\n\
private /users/<your name>/ directory.";
}