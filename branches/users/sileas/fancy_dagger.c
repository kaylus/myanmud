/* fancy_dagger.c
    stolen from the realm's second weapon*/

#include <config.h>

inherit WEAPON;

void create() {
    set_short ("[1m[35mfancy dagger[0m") ;
    set_long (wrap("A fancy dagger that is pink and fancy, you suspect that \
it serves better as a butter knife than as a real weapon.\n",72)) ;
    set_id ( ({ "dagger", "fancy dagger", "weapon" }) ) ;
    set_type ("cut");
    set_accuracy (25);
    set_damage ( ({ 20, 5 }) );
        set_verbs_me (({ "stab", "slash", "slit" }));
        set_verbs_other (({ "stabs", "slashes", "slits" }));
        set_offhand();
}
