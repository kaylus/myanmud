/* blackdragon.c
 * Empacher
 */
#include <config.h>
inherit MONSTER ;

void create () {

        ::create() ;
	set_id( ({ "dragon", "black dragon", "Black dragon",
			"Virulent", "virulent" }) );
	set_short("[30m[1mVirulent, the black dragon[0m");
        set_long("\
   This enormous dragon is almost invisible in the room's inky\n\
darkness. However, its glowing yellow eyes reveal its location\n\
quickly. Its enormous forked tail, and powerful wings flail about\n\
in anger at your annoyance.\n" );
        set_health(500);
        set_weapon_name("claws");
        set_gender("female");
        enable_commands();
        /*set("esteem", 40);
	set("stat/strength", 40);
	set_resistance("acid", 100);
	set("exp", 30000);
	set("no_panic", 1);*/
	set_damage( ({ 30, 20 }) );
	set_accuracy(65);
	set_hit_func("specials");
}

int specials(object attacker, object victim) {

	object *dude;
        int dam, chance, i, size;
        string vname, vobj;

        if(random(100) < 80) return 0;
	vname = victim->query_cap_name();
	vobj = victim->query_objective();
	chance = random(10);
	switch(chance) {
        case 0..2:
                victim->catch_tell(
		"\nThe Black Dragon impales you with its tail!\n\n");
		attacker->query_environment()->room_tell("\n"+vname+
		" is impaled by the Black Dragon's tail!\n\n", victim);
                dam = random(10) + 30;
                victim->receive_damage(dam, attacker, "thrusting");
                return 0;
                break;
        case 3..9:
                victim->query_environment()->room_tell( "[31m[1m"+
"\nThe Black Dragon spews a massive spittle of acid around the room,\n"+
"covering you in its corrosive death...[0m\n\n");
                dude = attacker->query_environment()->query_inventory();
                size = sizeof(dude);
                for(i=0; i<size; i++) {
                   	if(!dude[i]->query_has_health()) continue;
                   	if(dude[i]==attacker) continue;
                   	dam = random(20) + 50;
                   	dude[i]->receive_damage(dam, attacker, "acid");
                   	dude[i]->attack(attacker);
                   	}
                break;
        default:
                return 0;
                break;
                }
        return 0;
}

void die() {

        /*object coins;*/

		this_object()->query_environment()->room_tell(
			"The massive Black Dragon falls to the ground with a lifeless thud.\n");
        /*coins = clone_object("/std/coins") ;
        coins->set_number(200);
        coins->set_type("eagle");
        coins->move(this_object());*/
        ::die();
}
