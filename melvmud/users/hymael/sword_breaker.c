/* Citali, the Swordbreaker */

inherit WEAPON;

void create() {
    set_short ("[31mCitali, the Swordbreaker[0m") ;
    set_long (wrap("Citali is a medium-sized dagger designed to be in the offhand. \
It is a twisted thing, with twines lacing its entire length.  It looks as though it was \
tortured at the forge.  Its many hooks and crevices snag weapons and break them like dry \
twigs.\n",72)) ;
    set_id ( ({ "citali", "Citali", "swordbreaker", "dagger" }) ) ;
    set_type ("cut");
    set_accuracy (5);
    set_quality(1000);
    set_damage ( ({ 2, 2 }) );
   	set_verbs_me (({ "strike", "slash" }));
   	set_verbs_other (({ "strikes", "slashes" }));
   	set_offhand();
   	set_intercept_func("sword_break");
   	set_speed(5);
}

int sword_break(object owner, object attacker, object weapon){

	if(random(100) < 6){/* successful intercept */
		string oname, aname, wname;
		oname = owner->query_cap_name();
		aname = attacker->query_cap_name();
		wname = weapon->query_weapon_name();
		owner->catch_tell("[31mCitali catches "+aname+"'s [0m"+wname+"[31m in its tines.[0m\n");
		attacker->catch_tell("[31m"+oname+"'s strange weapon catches your [0m"+wname+"[31m in its tines.[0m\n");
		attacker->query_environment()->room_tell(oname+"'s strange weapon intercepts "+
												 aname+"'s attack.\n",
												 ({ owner, attacker }) );

		weapon->handle_break(attacker, this_object());
		return 1;
	}
}
