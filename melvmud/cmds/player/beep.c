/* beep - Hymael */

#define BEEP ""

int do_command(string str){
    object person;

    if(!str){
		write(BEEP+"You beep.\n");
		say(BEEP+TPN+" beeps.\n");
		return 1;
	}

	person = TP->query_environment();

	if(!person)
		return fail_msg("No one by that name to beep.\n");

	person = person->present(str);

	if(!person)
		return fail_msg("No one by that name to beep.\n");

	write(BEEP+"You beep "+person->query_cap_name()+".\n");
	say(BEEP+TPN+" beeps "+person->query_cap_name()+".\n",
	    ({ person }) );

	person->catch_tell(BEEP+TPN+" beeps you.\n");

	return 1;
}

string help(){
	return "\n\
This command allows you to beep.";
}