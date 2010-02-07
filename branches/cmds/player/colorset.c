/* Colorset command
   -Hymael
*/

#include <options.h>
#include <config.h>

#define SYNTAX "Usage: colorset <channel> [bold] color\n"
#define COLORABLE CHANNELS + ({ "say", "tell" })
#define COLORS ({"black","red","green","orange","yellow","blue","magenta","pink","cyan","none"})

int do_command (string str) {
    string channel, color, *indices;
    mapping colorsets;
    int bold,i;
    if(!str){/* comprehensive listing */
	write("Your color settings:\n");
	colorsets = TP->query_colors();
	indices = map_indices(colorsets);
	if(!indices || (i=sizeof(indices))==0)write("No colors set.\n");
	while(--i >= 0){
	    write("- "+colorsets[indices[i]]+indices[i]+"[0m\n");
	}
	return 1;
    }
    bold=0;
    /* check if it's a daemon channels */
    if(sscanf(str, "%s bold %s", channel, color)==2){
	bold=1;
    }else if(sscanf(str, "%s %s", channel, color)!=2){
	return fail_msg(SYNTAX);
    }
    /* channel now contains channel and color contains color with bold set */

    if (member_array(channel, COLORABLE)>-1) {
	if (member_array(channel, WIZ_CHANNELS)>-1 &&
	  !TP->query_wizard()) {
	    return fail_msg(SYNTAX);
	} else {
	    if(member_array(color, COLORS)==-1)
		return fail_msg("Faulty color.\n");

	    /* parse into a color */
	    switch(color){
	    case "black":	color="";
		if(bold)color += "[1m";
		color += "[30m";
		break;
	    case "red": 	color="";
		if(bold)color+="[1m";
		color += "[31m";
		break;
	    case "green": 	color="";
		if(bold)color+="[1m";
		color += "[32m";
		break;
	    case "orange":	if(bold)return fail_msg("Faulty color.\n");
		color = "[33m";
		break;
	    case "yellow":	if(bold)return fail_msg("Faulty color.\n");
		color = "[33m[1m";
		break;
	    case "blue":  	color="";
		if(bold)color+="[1m";
		color += "[34m";
		break;
	    case "magenta":	if(bold)return fail_msg("Faulty color.\n");
		color = "[35m";
		break;
	    case "pink":	if(bold)return fail_msg("Faulty color.\n");
		color = "[35m[1m";
		break;
	    case "cyan": 	color="";
		if(bold)color+="[1m";
		color += "[36m";
		break;
	    default:		color="[0m";
		if(bold)color += "[1m";
		break;
	    }/* color parsed */
	    if(TP->set_color(channel, color)){
		write("["+channel+"] set to "+((bold)?("bold "):(""))+color+"this.[0m\n");
	    } else {
		write("Colorset failed.\n");
	    }

	}
    }else{
	return fail_msg(SYNTAX);
    }
    return 1;
}

string help(){
    return SYNTAX+"\n\
This command sets the color of a given channel.\n";/* add in color help */
}
