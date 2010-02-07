/********
 * ship *
 ********/

inherit "/inherit/ship_room.c";

void create(){
	::create();
	/* create other rooms */
	set_short("Helm");
	set_long("This is the helm.\n");
	set_helm(1);
}