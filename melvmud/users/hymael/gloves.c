/* test subject */

inherit "/inherit/armor.c";

void create(){
	set_short("mighty gauntlets");
	set_long("This is a pair of mighty gauntlets.\n");
	set_id( ({ "gauntlets", "mighty gauntlets" }));
	set_type("gauntlet"); set_ac(12);
}
