/* diamond */

inherit "/inherit/tradeskills/component.c";

create(){
	set_tradeskill("weaponsmithing");
	set_short("diamond");
	set_long("This is diamond, very difficult but very strong.\n");
	set_alloy("diamond");
	set_bonus(20);
	set_difficulty(20);
	set_subset("alloy");
	set_color("[36;1m");
	set_id( ({ "diamond" }) );
}