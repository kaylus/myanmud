#include <config.h>

#define SYNTAX "Usage: unalias <name>\n"

int do_command (string str) {
	if(!str) return fail_msg(SYNTAX);
	/* display alias for str */
	switch(TP->remove_alias(str)){
		case 0: write("Alias ("+str+") not found.\n");
				break;
		default: write("Alias ("+str+") removed.\n");
	}
	return 1 ;
}
string help(){
	return SYNTAX+"\n\
This command allows you to remove an alias that has\n\
been entered with the alias command.\n\n\
See also: alias";
}
