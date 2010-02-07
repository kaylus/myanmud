/* The inventory command. Show a player the short of everything in his
   possession.
   Mobydick, 7-14-94.
*/
#include <weight.h>

int do_command(){
    object *stuff;
    string name, str;
    int i, sz, p_cap, p_volume, max_volume, max_cap;

    p_cap = TP->query_p_cap();
    p_volume = TP->query_p_volume();
    max_cap = TP->query_capacity();
    max_volume = TP->query_volume();

    str = " Carried: ["+p_cap+" / "+max_cap+"] "+WEIGHT_UNIT+"s\n";

    stuff = TP->query_inventory();
    if(!stuff || !(sz=sizeof(stuff))){
        write(str+"\nYou are empty-handed.\n");
		return 1;
    }
    for(i=0; i<sz; i++){
        name = stuff[i]->query_short();
		/* If it has no short it shouldn't show up in your inventory list. */
		if (!name || !strlen(name))
			continue;

		str += "  "+capitalize(name)+"\n";
    }
    write(str);
    return 1;
}
