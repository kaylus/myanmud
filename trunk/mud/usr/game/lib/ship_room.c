/**************
 * ship rooms *
 **************/

inherit LIB_ROOM;
#include <type.h>

object _ship;  /**< ship associated with this room */
int is_helm;  /**< whether this room is a helm */
int is_deck;  /**< whether this room is the main deck */

void create(varargs int clone){
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

mixed ahoy(string str){
    mixed val;
    val = _ship->ahoy(str);
    if(typeof(val)==T_INT){
	this_player()->message("You ahoy to your shipmates, \""+capitalize(str)+"\"\n");
    }
    return val;
}

mixed steer(string str){
    if(!is_helm)
	return "You can only steer this vessel from the helm!\n";

    return _ship->change_heading(str);
}

mixed lower(string str){
    if(!is_deck)
	return "You can only lower the gangplank or anchor from the main deck!\n";

    if(!str || (str != "anchor" && str != "gangplank"))
	return "Usage: lower <anchor/gangplank>\n";

    if(str == "anchor"){/* lower anchor */
	if(!(_ship->lower_anchor())){
	    this_player()->message("Anchor is already lowered.\n");
	}else{
	    _ship->ahoy("The vessel's anchor splashes into the water.\n", this_player());
	    this_player()->message("You lower the vessel's anchor into the water.\n");
	}
    }else{/* lower gangplank */
	int result;
	result = _ship->lower_plank();
	if(result == 1){/* lowered successfully */
	    _ship->ahoy("The vessel's gangplank lowers to the port.\n" , this_player());
	    this_player()->message("You lower the gangplank to port.\n");
	}else if(result == -1){
	    this_player()->message("The vessel's anchor must be set first.\n");
	}else if(result == 2){
	    this_player()->message("The gangplank is already lowered.\n");
	}else{
	    this_player()->message("You're not at a port, do you wish to walk the plank?\n");
	}
    }
    return 1;
}

mixed raise(string str){
    if(!is_deck)
	return "You can only raise the gangplank or anchor from the main deck!\n";

    if(!str || (str != "anchor" && str != "gangplank"))
	return "Usage: raise <anchor/gangplank>\n";

    if(str == "anchor"){/* raise anchor */
	int result;
	if((result = _ship->raise_anchor()) == -1){
	    this_player()->message("You must raise the gangplank first.\n");
	}else if(result == 0){
	    this_player()->message("The anchor isn't presently lowered.\n");
	}else{
	    _ship->ahoy("The vessel's anchor rises from the water.\n", this_player());
	    this_player()->message("You raised the anchor.\n");
	}
    }else{/* raise gangplank */
	int result;
	result = _ship->raise_plank();
	if(result == 0){/* raised successfully */
	    this_player()->message("The gangplank is already raised.\n");
	}else{
	    _ship->ahoy("The vessel's gangplank is quickly raised.\n" , this_player());
	    this_player()->message("You raised the gangplank.\n");
	}
    }
    return 1;
}

mixed check(string str){
    if(!str || str != "heading")
	return "Usage: check <heading>\n";

    this_player()->message("You determine that the vessel's heading is "+_ship->query_dir()+".\n");
    return 1;
}

void set_plank(object room){
    add_exit("port", room);
}

void raise_plank(){
    remove_exit("port");
}

string query_long(varargs int brief){
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
    value += "%^BOLD%^\n\t";
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
    value += "\n%^RESET%^";
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
		LOGD->log("this_player in ship_room = "+object_name(this_player()), "braind");
	    if(inventory[i] == this_player())
		continue;

	    name = inventory[i]->query_short();
	    if(name){
		value += "   "+capitalize(name)+"\n";
	    }
	}
    }
    return value;
}
