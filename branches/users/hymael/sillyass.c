/* Test monster */

#include <config.h>

inherit MONSTER ;

void create() {
    set_short ("Sillyass") ;
    set_long ("Sillyass, the brainful wonder beast.\n") ;
    set_id ( ({ "sillyass" }) ) ;
    enable_commands();
    set_greeting("$N sneezes on you.");
    set_health(5000);
    set_gender("female");
    ::create();
}
