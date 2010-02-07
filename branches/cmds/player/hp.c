/* The hp command
	Hymael - this will eventually become a more abstract returned value
*/

int do_command (string str) {
	write("Status:");
	write(TP->query_diagram());
	return 1;
}

string help(){
	return "This command returns your present health.\n\n";
}
