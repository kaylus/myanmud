/*
 * the hp command
 */
inherit BODY_COMMAND;

mixed cmd_hp(string cmd, string args, object actor){
    actor->message("hp "+actor->query_health()+" / "+actor->query_max_health()+"\n");
    return 1;
}

mixed help(string cmd, object actor){
	return "The hp command prints your current health.\n";
}