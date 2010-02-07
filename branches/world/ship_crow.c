/********
 * ship *
 ********/

inherit "/inherit/ship_room.c";

void create(){
	::create();
	/* create other rooms */
	set_short("The Crow's Nest");
	set_long("This is the crow's nest.\n");
}