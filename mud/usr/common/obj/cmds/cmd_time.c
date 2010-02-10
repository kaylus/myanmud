/*
 * the time command
 * TODO: debug 0 minutes and seconds
 */

inherit BODY_COMMAND;

mixed help(string cmd, object actor){
	return "Used to get game time.\n";
}

/* channeld */
mixed cmd_time (string cmd, string str, object actor){
	mapping time;
	time = "/usr/common/sys/weatherd"->get_date();
    actor->message("/usr/common/sys/weatherd"->format_time(time)+"\n");
    return 1;
}