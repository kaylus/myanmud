/*
   ocean.c
   The ocean room. Used for testing movement.
   Mobydick, 5-28-94.
*/

#include <config.h>

inherit "/inherit/portage.c";

void create() {
    set_short ("[36mSwimming in the ocean[0m") ;
    set_long (
"You are swimming deep below the ocean waves, among the fish and the whales.\n"
        );
    set_exits ( ([ "north" : "/world/start" ]) ) ;
}
