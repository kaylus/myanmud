/* A limb */

#define DECAY_TIME 20

inherit CONTAINER;
inherit WEAPON;

private int state;
private string name;
private int handle;

void create(varargs int clone) {
    set_short ("a limb") ;
    set_long ("The limb of a fallen.\n");
    set_id ( ({ "limb", "a limb" }) ) ;
    handle = call_out("decay", DECAY_TIME);
    state = 0; /* 0 fresh, 1 decayed, 2 rank, gone */
    name = "";
}

int is_limb(){ return 1; }

void set_limb(string name, string part){
    name = capitalize(name);
    set_short(name+"'s "+part);
    set_long(name+"'s "+part+", they'd appreciate if you returned it.\n");
    id += ({ lower_case(name)+"'s "+part, part });
}

void decay(){
    object *stuff;
    int sz;
    switch(++state){
    case 1:
	set_short(name+"'s decaying limb");
	break;
    case 2:
	set_short(name+"'s rotting limb");
	break;
    default:
	this_object()->query_environment()->message("The limb rots away.\n");
	stuff = this_object()->query_inventory() ;
	if (stuff && (sz=sizeof(stuff))>0) {
	    while(--sz>=0){
		stuff[sz]->move(this_object()->query_environment());
	    }
	}
	destruct();
	return;
    }
    handle = call_out("decay", DECAY_TIME);
}

void stop_decay(){
    remove_call_out(handle);
}

