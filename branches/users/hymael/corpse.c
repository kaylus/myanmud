/* demo corpse */

#include <config.h>

inherit corpse "/inherit/corpse.c" ;

void create() {
    ::create();
    corpse::set_name ("sileas") ;
}
