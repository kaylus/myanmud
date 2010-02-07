/* sileas's test cloak*/

inherit "/inherit/armor.c";

void create(){
        set_short("[1m[30mManteau de la Deesse[0m");
        set_long("This is a black, velvety cloak embroided with a silver rose.\n");
        set_id( ({ "manteau", "cloak", "coat", "manteau de la Deesse" }));
        set_type("cloak");
        set_ac(50);
        set_equip_func ("equip") ;
        set_unequip_func ("unequip") ;
}       

        int equip(){
	        write(wrap("The cloak falls freely from your shoulder, you feel blessed.\n",72));
	        say(wrap(TPN+" puts on the cloak. Blinding light radiates from the \
	        silver rose.\n", 72));
	        return 1 ;
}
	
	int unequip(){
	        write(wrap("You remove the cloak from your shoulder and the blessing \
	        fades.\n",72));
	        say(wrap(TPN+" removes the cloak and the silver rose darkens.\n",72));
	        return 1;
}
