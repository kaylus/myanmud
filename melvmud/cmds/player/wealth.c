/* Wealth command
   -Hymael
 */
#include <money.h>

int do_command(){
    mapping wealth;
    int i, sz;
    string str;

    str = "Wealth:\n\n";
    wealth = TP->query_wealth();
    if(!wealth)
	return fail_msg("You are carrying no coins.\n");

    sz = sizeof(COIN_NAMES);
    for(i=0,sz = sizeof(COIN_NAMES); i<sz; i++){
	str += pad(capitalize(COIN_NAMES[i])+":", 15)+(int)wealth[COIN_NAMES[i]]+"\n";
    }
    write(str);
    return 1;
}

string help(){
    return "This command tells you what is in your purse.\n";
}
