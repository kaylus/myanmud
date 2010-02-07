/* insane armor */

inherit ARMOR;

void create(){
	set_short("[34mindigo breastplate[0m");
	set_long(wrap("This breastplate drips of blood.  Large furrows run across the chest "+
"in a design that captivates the eye.\n", 72));
	set_id( ({ "breastplate", "indigo breastplate" }) );
	set_type("suit");
	set_slot("torso");
	set_ac(10);
}
