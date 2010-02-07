/********
 * ship *
 ********/

inherit "/inherit/ship_room.c";

void create(){
	::create();
	/* create other rooms */
	set_short("Fore Deck");
	set_long("This is the fore deck.\n");
}