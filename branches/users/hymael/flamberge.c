/* realm's third weapon */

#include <config.h>

inherit WEAPON;

void create() {
    set_short ("[31ma massive flamberge[0m") ;
    set_long (wrap("This is a massive flamberge.  \
You feel as though it could tear through sinew with ease.\n",72)) ;
    set_id ( ({ "flamberge", "massive flamberge" }) ) ;
    set_type ("cut");
    set_accuracy (2);
    set_quality (40);
    set_speed (7);
    set_damage ( ({ 190, 10 }) );
   	set_verbs_me (({ "strike", "gut" }));
   	set_verbs_other (({ "strikes", "guts" }));
   	set_two_handed();
}
