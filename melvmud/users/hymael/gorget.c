/* insane armor */

inherit "/inherit/armor2.c";

void create(){
	set_short("[34mindigo gorget[0m");
	set_long(wrap("This is a gorget for an indigo set.\n", 72));
	set_id( ({ "gorget", "indigo gorget" }) );
	set_type("gorget");
	set_slot("head");
	set_ac(5);
}