/********
 * ship *
 ********/

inherit "/inherit/ship_room.c";

void create(){
	::create();
	/* create other rooms */
	set_short("Quarter Deck");
	set_long("This is the quarter deck.\n");
}