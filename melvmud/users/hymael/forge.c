/* a magical forge */

inherit OBJECT;

void create() {
    set_short ("[33mmagical forge[0m") ;
    set_long (wrap("This forge can be used to repair broken weapons or \
armor.\n",72)) ;
    set_id ( ({ "forge", "magical forge" }) );
    add_command("repair", "repair") ;
}

int repair(string str){
	object thing;

	if(!str) return fail_msg("What item do you wish to repair?\n");

	if(!(thing = TP->present(str)))
		return fail_msg("Cannot find "+str+" to fix.\n");

	if(!thing->is_armor() && !thing->is_weapon())
		return fail_msg("That isn't a piece of armor or a weapon.\n");

	if(!thing->is_broke())
		return fail_msg("That thing is already in fine shape.\n");

	thing->fix_break();

	TP->catch_tell(wrap("You persuade the forge to action and a massive sledge appears.  \
The sledge, hovering in the air under its own control, proceeds to pound out and repair \
the damages to the "+str+".\n",72));

	ETP->room_tell(wrap(TPN+" persuades the forge to action and a massive sledge appears.  \
The sledge, hovering in the air under its own control, proceeds to pound out and repair \
the damages to the "+str+".\n",72), ({ TP }) );
	return 1;
}