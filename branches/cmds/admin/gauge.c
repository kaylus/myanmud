/*********************************
 * This command outputs the cost *
 * of the command after gauge    *
 * -Hymael                       *
 *********************************/
#include <status.h>

int do_command(string str){
	int ticks, temp;
	float time, temp2;


	time = (float)millitime()[0] + millitime()[1];      /* time at start */
	ticks = status()[ST_TICKS]; /* ticks at beginning */

	TP->command(str);

	temp = status()[ST_TICKS]; /* for accurate resolution */
	temp2 = (float)millitime()[0] + millitime()[1];
	ticks -= temp;
	time = temp2 - time;
	write("\n\nTime:  "+time+"\nTicks:  "+ticks+"\n");

	return 1 ;
}

string help(){
	return "This command determines a commands tick usage and time.\n";
}