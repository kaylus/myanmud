/* insane armor */

inherit ARMOR;

void create(){
	set_short("[34mindigo helm[0m");
	set_long(wrap("This is a helm for an indigo set.\n", 72));
	set_id( ({ "helm", "indigo helm" }) );
	set_type("helm");
	set_slot("head");
	set_ac(5);
}
