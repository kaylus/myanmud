/* a berserk - Hymael */
#define SYNTAX "Usage: berserk\n"

int do_command (string str) {
    if(!TP->query_in_combat()){
		return fail_msg("You're not presently in combat.\n");
	}
	write("You begin your devestating onslaught.\n");
	say("[33m[1m"+TPN+" flies into a [31mberserker rage![0m\n");
	TP->execute_attack(random(10) + 5);
	return 1;
}

string help(){
	return SYNTAX+"\n\
This command allows you to berserk.";
}