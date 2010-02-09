/*
 * the bug command
 */

inherit BODY_COMMAND;

mixed help(string cmd, object actor){
	return "Used to report a bug.\n";
}

/* rudimentary bug reporting */
mixed cmd_bug (string cmd, string str, object actor){
	actor->message("working on it\n");
	return 1;
}