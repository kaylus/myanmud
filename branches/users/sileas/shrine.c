/*shrine.c
Shrine of the King Squid*/

#include <config.h>

inherit ROOM;

void create() {
        set_short ("[1m[33mShrine[0m") ;
        set_long (wrap("You have reached the shrine where no man has come \
before. This is a bizarre shrine dedicated to the [1m[31mKING SQUID[0m.\n", 72)) ;
        set_exits ( ([ "south" : "/users/sileas/ocean1" , "hole" : "/users/sileas/chamber"]) ) ;
}
