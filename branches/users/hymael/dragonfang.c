/* dfang */

#include <config.h>
inherit WEAPON;

void create() {

    set_id(({ "Dragonfang", "fang", "dagger", "dragonfang" }));
	set_short("[34mDragonfang[0m");
	set_long("This magnificent dagger is crafted of a flawless, dark blue steel.\n\
The blade is slightly curved, and you imagine the additional cruelty\n\
it must inflict when pulled free of its victim's flesh.\n\
   Examining the blade more closely, you notice an occasional flicker\n\
of electricity crackling along its length.\n");
	set_accuracy(20);
	set_damage( ({ 4,14 }) );
	set_type("pierce");
	set_verbs_me(({ "sink into", "pierce", "rupture", "stab"}) );
	set_verbs_other(({ "sinks into", "pierces", "ruptures", "stabs"}) );
	set_wield_func("wld");
	set_unwield_func("unwld");
	set_hit_func("specials");
}

int wld() {
	write("Dragonfang quickly wriggles from your grasp.\n");
	return 0;
	/*	}
        tp->modify_resistance( "electricity", 75, -1 );
	write("As you grasp %^BLUE%^Dragonfang%^RESET%^"+
		" an electrical surge tingles your arm.\n");
	return 1;*/
}

int unwld() {

	/*object tp;

	tp = this_player();
	if (!tp) {
// This happens if you go net-dead and get dumped. Let's try the
// environment?
	    tp = environment(this_object()) ;
	    if (!tp) {
// I give up. Curse Empacher and his idiot tp variable anyway.
		return 1 ;
	    }
	}
        tp->remove_resistance_bonus( "electricity", 75 ) ;*/
        write("As you release your grasp upon [34mDragonfang[0m"+
		" your arm feels numb and lifeless.\n");
	return 0;
}

int specials(object attacker, object victim) {

	int dam, type;
	string name, vname, vposs;

	if(random(100) > 25) return 0;
	name = attacker->query_cap_name();
	vname = victim->query_cap_name();
	type = random(10);
	switch(type) {
	case 0..1:
		attacker->catch_tell(
"An enervating surge of electricty courses through your body!\n");
		dam = random(10) + 10 ;
		attacker->receive_healing(dam);
		/*attacker->delta_sp(dam);
		ttacker->delta_ep(dam*2);*/
		return 0;
		break;
	case 2..3:
		vposs = victim->query_possessive();
		attacker->catch_tell(
"A shocking bolt of energy surges into "+vname+" freezing "+vposs+
" central nervous system completely!\n");
		victim->catch_tell(
"A shocking bolt of energy surges into you freezing your\n"+
" central nervous system completely! ACK!!!!!!!!!!\n");
		dam = 4 + random(6);
		victim->block_attack(dam);
		return 0;
		break;
	case 4..8:
		attacker->catch_tell("[34mDragonfang[0m cooks "+
vname+" with a powerful blast of electricity!\n");
		victim->catch_tell(
"You are cooked by a powerful blast of electricity!\n");
		victim->query_environment()->room_tell( vname+
		" is cooked by a powerful blast of electricity from\n"+
		name+"'s deep blue dagger.\n", ({ attacker, victim }) );
		dam = random(10) + 20;
		victim->receive_damage(dam, attacker, "electricity");
		return 0;
		break;
	case 9:
		vposs = victim->query_possessive();
		attacker->catch_tell("\n[34mDragonfang[33m[1m fills "+
		   vname+" with a horrible blast of electric energy!\n"+
		   vname+"'s eyes bulge freakishly and "+vposs+
		   " mouth spews frothy gore.[0m\n\n");
		victim->catch_tell("[33m[1m"+name+
"'s dagger fills you with a horrible blast of electric energy!\n"+
"Your eyes bulge freakishly and your mouth spews frothy gore![0m\n");
		victim->query_environment()->room_tell("[33m[1m"+name+
"'s dagger fills "+vname+" with a horrible blast of electric energy!\n"+
vname+"'s eyes bulge freakishly and "+vposs+
" mouth spews frothy gore![0m\n", ({ attacker, victim }) );
		dam = random(20) + 50;
		victim->receive_damage(dam, attacker, "electricity");
		return 0;
		break;
	default:
		return 0;
		break;
		}
	return 0;
}
/*
int bye_bye() {

	tell_room(environment(TO), "%^BOLD%^WHITE%^Dragonfang twinkles for a moment then disapears.%^RESET%^\n");
        remove();
}*/
