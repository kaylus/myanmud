#include <kernel/user.h>
#include <config.h>
#include <status.h>

static void create (varargs int clone){
  	if (!find_object (SYSTEM_USER))
    	compile_object (SYSTEM_USER);
  	USERD->set_binary_manager (0, this_object ());
}

object select (string str){
  	return clone_object (SYSTEM_USER);
}

int query_timeout (object connection){
  	return DEFAULT_TIMEOUT;
}

string query_banner (object connection){
	return "\033[18mS.O.S.S.\n(" + status()[ST_VERSION] +")\n\nWhat's thy name? \033[0m";
}
