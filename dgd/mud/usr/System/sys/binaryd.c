#include <kernel/user.h>
#include <config.h>

static void create (varargs int clone){
  	if (!find_object (SYSTEM_USER))
    	compile_object (SYSTEM_USER);
  	USERD->set_binary_manager (0, this_object ());
}

object select (string str){
  	LOGD->log("Str = " + str + "\n", "log_select");
  	return clone_object (SYSTEM_USER);
}

int query_timeout (object connection){
  	return DEFAULT_TIMEOUT;
}

string query_banner (object connection){
  	return "\033[18mS.O.S.S.\nWhat's your name? \033[0m";
}
