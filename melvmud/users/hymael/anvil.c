/* an anvil */

inherit "/inherit/tradeskills/anvil.c";

void create() {
    set_short ("[33ma massive anvil[0m") ;
    set_long (wrap("This anvil can be used to shape and create weaponry.\n",72)) ;
    set_id ( ({ "anvil" }) );
    set_grade(5);
    ::create();
}
