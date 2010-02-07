/********
 * ship *
 ********/

inherit "/inherit/ship_room.c";

void create(){
	::create();
	/* create other rooms */
	set_short("Main Deck");
	set_long("This is the main deck.\n");
	set_deck(1);
}
