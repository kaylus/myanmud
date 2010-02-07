/* test subject */

inherit ARMOR;

void create(){
	set_short("[1ma coruscant shield[0m");
	set_long("This shield shines brightly, illuminating its owner with its brightness.\n");
	set_id( ({ "shield", "coruscant shield" }));
	set_type("shield");
	set_slot("arm");
	set_ac(10);
	set_equip_func("equip");
	set_unequip_func("unequip");
}

int equip(){
	write(wrap("You feel the shield's bright surface jump about to protect your every front.\n",72));
	say(wrap(TPN+" equips the shield and you face a blinding light.  The shield appears to be everywhere at once.\n", 72));
	return 1;/* denotes messages handled */
}

int unequip(){
	write(wrap("You feel the shield's bright surface dim as you unequip it.\n",72));
	say(wrap(TPN+" unequips the shield and the bright light dissipates.\n", 72));
	return 1;/* denotes messages handled */
}
