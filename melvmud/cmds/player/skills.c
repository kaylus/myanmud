/* skills
   -Hymael
*/

#define SYNTAX "Usage: skills\n"

int do_command (string str) {
	mapping skills;
	string *indies;
	int i;

	skills = TP->query_skills();
	if(!skills)
		return fail_msg("No Skills.\n");

	indies = map_indices(skills);
	i = sizeof(indies);

	str = "Skills:\n";
	while(i--){
		str += " "+pad(capitalize(indies[i])+":", 15)+skills[indies[i]]+"\n";
	}

	write(str);
    return 1;
}

string help(){
	return SYNTAX+"\n\
This command shows you your skills.\n";
}