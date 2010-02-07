/* score
   -Hymael
*/

#include <options.h>
#include <config.h>

#define SYNTAX "Usage: score\n"

int do_command (string str) {
	mapping stats;
	int i;
	string score, *attributes;
	/* temp */
	/*TP->roll_stats();
	/* temp */

	stats = TP->query_stats();
	attributes = map_indices(stats);
	i = sizeof(attributes);

	score = TPN + "\n";
	score += TP->query_diagram();

	while(i--){
		score += "[36;1m"+pad(capitalize(attributes[i])+": ", 15)+"[0m"+stats[attributes[i]]+"\n";
	}

	write(score);
    return 1;
}

string help(){
	return SYNTAX+"\n\
This command shows you your stats.\n";/* add in color help */
}