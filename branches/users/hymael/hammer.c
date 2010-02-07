/* an anvil */

inherit "/inherit/tradeskills/component.c";

void create() {
	set_tradeskill("weaponsmithing");
    set_short ("a weaponsmith's hammer") ;
    set_long (wrap("This is a hammer.\n",72)) ;
    set_id ( ({ "hammer" }) );
    set_subset("hammer");
}
