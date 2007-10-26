/*
 * the alias inheritable for a user
 */
 
#include <alias.h>

mapping aliases; /* mapping for aliases */

void create(varargs int clone){
	aliases = DEF_ALIASES;
}

string add_alias(string alias, string command){
	if(!aliases){
		aliases = DEF_ALIASES;
	}
	
	if(aliases[alias] == nil){/* no previous alias */
		aliases[alias] = command;
		return "Created alias " + alias + ": " + command + ".\n";
    	}else{/* previous alias */
		aliases[alias] = command;
		return "Alias changed to " + alias + ": " + command + ".\n";
	}
 	return alias;
}
		
string remove_alias(string alias){/* remove an alias */
	if(!aliases){
		aliases = DEF_ALIASES;
	}
	
	if(aliases[alias] == nil){ 
		return "No existing alias to remove.\n";
	}else{
		aliases[alias] = nil;
		return "Alias " + alias + " removed.\n";
	}	
	return alias;
}

string query_alias(string alias){
	if(!aliases){aliases = DEF_ALIASES;}

	if(!aliases[alias]){return alias;}/* no existing alias */

	return aliases[alias];
}

	
