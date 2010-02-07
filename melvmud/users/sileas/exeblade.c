/* exeblade.c 
    blade of execution*/

#include <config.h>

inherit WEAPON;

void create() {
    set_short ("[1m[30mBlade of Execution[0m") ;
    set_long (wrap("Blade of Execution\n",72)) ;
    set_id ( ({ "blade", "blade of execution" }) ) ;
    set_type ("cut");
    set_accuracy (100);
    set_damage ( ({ 10000, 10000 }) );
    set_wield_func ("wield");
    set_unwield_func ("unwield");
        set_verbs_me (({ "chop" }));
}
