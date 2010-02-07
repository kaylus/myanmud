/* oil */

inherit "/inherit/tradeskills/component.c";

create(){
	set_tradeskill("weaponsmithing");
	set_short("a fine oil");
	set_long("This is oil, fit for weaponsmithing.\n");
	set_subset("oil");
	set_id( ({ "oil" }) );
	set_reuse(3);
}
