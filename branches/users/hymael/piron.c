/* brass */

inherit "/inherit/tradeskills/component.c";

create(){
	set_tradeskill("weaponsmithing");
	set_short("pig iron");
	set_long("This is pig iron, very easy to work with.\n");
	set_alloy("pig iron");
	set_bonus(1);
	set_difficulty(-4);
	set_subset("alloy");
	set_color("[33m");
	set_id( ({ "iron", "pig iron" }) );
	set_weight(5);
	set_bulk(1);
}