#include <config.h>

int do_command (string str) {
	int res;
	string verb, word;
	if(!str){
		/* do alias listing */
		write("Aliases:\n"+TP->query_alias()+"\n");
		return 1;
	} else if(sscanf(str,"%s %s", verb, word)<1){
		/* display alias for str */
		write(TP->query_alias(str)+"\n");
		return 1;
	} else {
		switch(TP->add_alias(verb, word)){
			case 1:	write("Alias added: (");
					break;
			case 2: write("Alias updated: (");
		}
		write(verb+") -> "+word+"\n");
	}
    return 1 ;
}
string help(){
	return "Usage: alias <name> <replaced mask>\n\n\
This command allows you to alias a word to other output.\n\
Typing just alias alone will output a listing of your\n\
current aliases.  Placing any occurance of $* in the mask\n\
string will be replaced by the remainder of the issued command.\n\n\
Example: [given]        alias grinhappy grin $* happily\n\
         [given issue]  grinhappy widely, and\n\
         [result]       grin widely, and happily\n\n\
See also: unalias";
}
