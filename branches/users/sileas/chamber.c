/*chamber.c
secret chamber
 */

#include <config.h>

inherit ROOM;

void create() {
        set_short ("[1m[30mA Secret Chamber[0m") ;
        set_long (wrap("You squeeze through the hole you found in \
the shrine and come to this dark, stone-built room. Strangely air, \
instead of water, filled this room. In the center of this enormous \
chamber stands a statue about 20 feet tall. You gasp at the sight of \
this statue, the statue of a GIANT Octopus, the mysterious \
Octopus race, which only appeared in legends.\n",72));
        set_exits ( ([ "hole" : "/users/sileas/shrine" ]) ) ;
}
