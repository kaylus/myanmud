/* brass */

inherit "/inherit/tradeskills/component.c";

void create(){
	set_tradeskill("weaponsmithing");
	set_short("silver pieces");
	set_long("This is silver, easily made into weapons.\n");
	set_alloy("silver");
	set_bonus(5);
	set_difficulty(3);
	set_color("[1m");
	set_subset("alloy");
	set_id( ({ "silver" }) );
}