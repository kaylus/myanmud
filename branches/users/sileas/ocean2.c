/*Ocean2.c
Under the Ocean */

#include <config.h>

inherit ROOM;

void create() {
        set_short ("[1m[34mUnder the Ocean[0m") ;
set_long (wrap("As you go deeper into the ocean, you discover some [1m[33mSHINING[0m stuff ahead of you.\n",72));
set_exits ( ([ "up" : "/users/sileas/ocean1", "north" : "/users/sileas/shrine"]) ) ;
}
