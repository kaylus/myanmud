/* pinkitite */

inherit "/inherit/tradeskills/component.c";

void create(){
	set_tradeskill("weaponsmithing");
	set_short("pinkitite ore");
	set_long(wrap("This is pinkitite, you can use this for weapons if you don't "+
"mind being labeled gay.\n", 72));
	set_alloy("pinkitite");
	set_bonus(1);
	set_difficulty(1);
	set_color("[35;1m");
	set_subset("alloy");
	set_id( ({ "pinkitite" }) );
}