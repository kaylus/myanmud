/* brass */

inherit "/inherit/tradeskills/component.c";

create(){
	set_tradeskill("weaponsmithing");
	set_short("brass pieces");
	set_long("This is brass, easily made into weapons.\n");
	set_alloy("brass");
	set_bonus(20);
	set_difficulty(15);
	set_subset("alloy");
	set_color("[33;1m");
	set_id( ({ "brass" }) );
}