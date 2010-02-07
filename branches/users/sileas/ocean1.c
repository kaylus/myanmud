/*Ocean1.c
Under the Ocean */

#include <config.h>

inherit ROOM;

void create() {
        set_short ("[1m[34mUnder the Ocean[0m") ;
        set_long (wrap("You submerged to the less explored part of the ocean. \ The surrounding is pitch black and dead quiet. \ You suspect that you have lost your senses.\n",72));
        set_exits ( ([ "up" : "/world/ocean", "down" : "/users/sileas/ocean2"]) ) ;
}
