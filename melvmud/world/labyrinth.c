/*
   labyrinth.c
   Post death room
   Hymael
*/

#include <config.h>

inherit ROOM ;

void create() {
    set_short ("[32mLabyrinth[0m") ;
    set_long (wrap(
"All around you, your movements echo throughout the vast expanses of the labyrinth. \
Decaying vines pock the area, concealing exits and perceived exits.  You have a difficult \
journey ahead of you.\n", 72)
        );
    set_exits ( ([ "north" : "/world/start" ]) ) ;
}
