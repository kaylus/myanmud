/* insane armor */

inherit ARMOR;

void create(){
	set_short("[34mindigo sleeve[0m");
	set_long(wrap("This is a right sleeve for an indigo set.\n", 72));
	set_id( ({ "sleeve", "indigo sleeve" }) );
	set_type("sleeve");
	set_slot("right arm");
	set_ac(5);
}
