/* goddess_whip.c
    stolen from the realm's second weapon*/

#include <config.h>

inherit WEAPON;

void create() {
    set_short ("[1m[30mFouet de la Deesse[0m") ;

    set_long (wrap("This holy weapon has been given by the Goddess whose \
name shall not be mentioned. Wielder of this weapon is thus blessed by her. \n",72)) ;
    set_id ( ({ "le fouet", "fouet", "whip", "whip of goddess" }) ) ;
    set_type ("blunt");
    set_accuracy (100);
    set_damage ( ({ 100, 20 }) );
        set_verbs_me (({ "whip", "strike", "lash", "thrash" }));
        set_verbs_other (({ "whips", "strikes", "lashes", "thrashes" }));
        set_offhand();
}
