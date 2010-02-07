/**************
 * ship rooms *
 **************/

inherit ROOM;

object _ship;  /* ship associated with this room */
int is_helm;  /* whether this room is a helm */
int is_deck;  /* whether this room is the main deck */

void create(){
	add_command("ahoy", "ahoy"); /* global channel */
	add_command("steer", "steer");/* change_heading */
	add_command("check", "check");/* check heading */
	add_command("lower", "lower");/* lower anchor or gangplank */
	add_command("raise", "raise");/* raise anchor or gangplank */
}

void set_ship(object ship){
	_ship = ship;
}

object query_ship(){
	return _ship;
}

void set_helm(int val){
	is_helm = val;
}

int query_helm(){
	return is_helm;
}

void set_deck(int val){
	is_deck = val;
}

int query_deck(){
	return is_deck;
}

int ahoy(string str){
	int val;
	val = _ship->ahoy(str);
	if(val){
		write("You ahoy to your shipmates, \""+capitalize(str)+"\"\n");
	}
	return val;
}

int steer(string str){
	if(!is_helm)
		return fail_msg("You can only steer this vessel from the helm!\n");

	return _ship->change_heading(str);
}

int lower(string str){
	if(!is_deck)
		return fail_msg("You can only lower the gangplank or anchor from the main deck!\n");

	if(!str || (str != "anchor" && str != "gangplank"))
		return fail_msg("Usage: lower <anchor/gangplank>\n");

	if(str == "anchor"){/* lower anchor */
		if(!(_ship->lower_anchor())){
			write("Anchor is already lowered.\n");
		}else{
			_ship->ahoy("The vessel's anchor splashes into the water.\n", TP);
			write("You lower the vessel's anchor into the water.\n");
		}
	}else{/* lower gangplank */
		int result;
		result = _ship->lower_plank();
		if(result == 1){/* lowered successfully */
			_ship->ahoy("The vessel's gangplank lowers to the port.\n" , TP);
			write("You lower the gangplank to port.\n");
		}else if(result == -1){
			write("The vessel's anchor must be set first.\n");
		}else if(result == 2){
			write("The gangplank is already lowered.\n");
		}else{
			write("You're not at a port, do you wish to walk the plank?\n");
		}
	}
	return 1;
}

int raise(string str){
	if(!is_deck)
		return fail_msg("You can only raise the gangplank or anchor from the main deck!\n");

	if(!str || (str != "anchor" && str != "gangplank"))
		return fail_msg("Usage: raise <anchor/gangplank>\n");

	if(str == "anchor"){/* raise anchor */
		int result;
		if((result = _ship->raise_anchor()) == -1){
			write("You must raise the gangplank first.\n");
		}else if(result == 0){
			write("The anchor isn't presently lowered.\n");
		}else{
			_ship->ahoy("The vessel's anchor rises from the water.\n", TP);
			write("You raised the anchor.\n");
		}
	}else{/* raise gangplank */
		int result;
		result = _ship->raise_plank();
		if(result == 0){/* raised successfully */
			write("The gangplank is already raised.\n");
		}else{
			_ship->ahoy("The vessel's gangplank is quickly raised.\n" , TP);
			write("You raised the gangplank.\n");
		}
	}
	return 1;
}

int check(string str){
	if(!str || str != "heading")
		return fail_msg("Usage: check <heading>\n");

	write("You determine that the vessel's heading is "+_ship->query_dir()+".\n");
	return 1;
}

void set_plank(object room){
	add_exit("port", room);
}

void raise_plank(){
	remove_exit("port");
}

varargs string query_long(int brief){
    string value;
    object *inventory;
    int sz;

	/* Start with whatever desc the room coder supplied. Give the short
       or the long desc, according to the brief argument. */
    if(brief)
    	value = _ship->query_name()+"'s "+short_desc+"\n";
    else
    	value = _ship->query_name()+"'s "+short_desc+"\n\n"+long_desc;

	/* Add in any exits there may be. */
	value += "[1m\n\t";
    if(!exits || !(sz = map_sizeof(exits))){
        value += "There are no obvious exits.\n" ;
    }else{
		string *indies;
		indies = map_indices(exits);

        switch(sz){
		case 1:
	    	value += "The only obvious exit is "+indies[0];
	    	break;
	    case 2:
	    	value += "Obvious exits are "+indies[0]+" and "+indies[1];
	    	break;
	    default:
			value += "Obvious exits are "+implode(indies[0..sz-2], ", ")+", and "+indies[sz-1];
		}
	    value += ".\n";
    }
    value += "\n[0m";
	/* List the contents of the room. */
    inventory = query_inventory();
    if(inventory && (sz = sizeof(inventory))){
		string name;
		int i;

        for(i=0; i<sz; i++){
       		/* Make sure there isn't an empty item in the inventory somehow. */
	    	if(!inventory[i])
	    		continue;

       		/* Don't include our own body in the list. */
	    	if(inventory[i] == TP)
	    		continue;

	    	name = inventory[i]->query_short();
	    	if(name){
	    		value += "   "+capitalize(name)+"\n";
        	}
        }
    }
    return value;
}