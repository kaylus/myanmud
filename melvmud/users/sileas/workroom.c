/*
 *  workroom.c
 *  Your workroom
 */

#include <config.h>

inherit ROOM;

void create() {
	/* notice beautiful identation */
	set_short ("[35mSileas' Private Library[0m") ;

	/*
	 *	now to chop up this fugly line
	 *  Hymael has done it
	 */

	set_long (wrap("This is more like a study than a library. It's dimly lit, \
and you only see a handful of bookshelves placed against the walls, \
they are half-empty, or half-full depends on how you look at them. There \
is a large table in the middle of the room but there is no chair. A few \
books were opened on the table: Coding 101, Newbie Wiz Handbook, and How \
to Prevent SARS. Pieces of paper scattered on the table and on the floor, \
and it looks like someone has been working hard taking notes. Right opposite \
to the door to GH, there is another door leading to the balcony.\n",72));
	set_exits ( ([ "start" : "/world/start", "gh" : "/users/hymael/gh", "balcony" : "/users/sileas/balcony" ]) ) ;
}
