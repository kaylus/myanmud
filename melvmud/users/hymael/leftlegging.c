/* insane armor */

inherit ARMOR;

void create(){
	set_short("[34mindigo legging[0m");
	set_long(wrap("This is a left legging for an indigo set.\n", 72));
	set_id( ({ "legging", "indigo legging" }) );
	set_type("legging");
	set_slot("left leg");
	set_ac(5);
}
