/* sileas's test armor*/

inherit "/inherit/armor.c";

void create(){
        set_short("[1m[30mArmure de la Deesse[0m");
        set_long("This is an unusual piece of armor. Forged by the magic of \
the Goddess whose name shall not be mentioned, the bearer of the armor \
must have had her blessing.\n");
        set_id( ({ "Armure", "armor", "armure de la deesse", "armor of the goddess" }));
        set_type("suit");
        set_ac(50);
        set_equip_func ("equip") ;
        set_unequip_func ("unequip") ;
}       

        int equip(){
	        write(wrap("An aura of protection surrounds you as you put on \
the holy armor.\n",72));
	        say(wrap(TPN+" is suddenly surrounded by a bright aura.\n", 72));
	        return 1 ;
}
	
	int unequip(){
	        write(wrap("The aura fades as you slip out of the holy armor.\n",72));
	        say(wrap(TPN+" appears more vulnerable as the aura fades.\n",72));
	        return 1;
}
