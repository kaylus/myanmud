/*
 *  workroom.c
 *  Hymael's workroom
 */

inherit "/inherit/portage.c";

void create() {
    set_short ("[31mHymael's Study[0m") ;
    set_long ("Hymael's study echoes with the cries of mutilated code.\n");
	set_exits ( ([ "start" : "/world/start",
"west" : "/users/hymael/gh",
                   "gh" : "/users/hymael/gh"
                 ]) ) ;
}
