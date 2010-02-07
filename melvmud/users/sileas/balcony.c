/*
balcony.c
balcony of library
 */

#include <config.h>

inherit ROOM;

void create() {
	set_short ("[36mA Big Balcony[0m") ;
	set_long (wrap("Stepping out from the library, you come to a BIG \
balcony overlooking the ocean. There is basically nothing on the \
balcony, but you realise that this is a good place to watch the sun \
rise, and a place to enjoy the sea breezes. The balcony is like 20 \
feet above the ocean. And if you have a death wish, you can jump off \
the balcony and swim or drown in the endless ocean.\n",72));
set_exits ( ([ "ocean" : "/users/sileas/ocean1", "library" : "/users/sileas/workroom"]) ) ;
}
