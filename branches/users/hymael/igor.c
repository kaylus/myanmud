/* Test monster */

#include <config.h>

inherit MONSTER ;

void create() {
    set_short ("Igor") ;
    set_long ("Igor, the brain-toting wonder monster.\n") ;
    set_id ( ({ "igor" }) ) ;
    enable_commands();
    set_health(750);
    set_gender("male");
    set_damage(({ 40, 30 }));
    set_accuracy(50);
    set_verbs_me(({ "slash", "strike", "cut" }));
    set_verbs_other(({ "slashes", "strikes", "cuts" }));
	set_weapon_name("claws");
	set_follow();
    ::create();
    set_hit_func("tornado");
}

int tornado(object attacker, object victim){
	int dam;
	switch(random(100)){
	case 0..20:
		dam = random(65)+1;
		attacker->catch_tell("[31m[1mYou fly into a tornado.[0m\n");
		victim->catch_tell("[31m[1m"+attacker->query_cap_name()+" flies into a vicious tornado, "+
				"tearing into your stomach with crazed, animalistic abandon![0m\n");
		attacker->query_environment()->room_tell("[31m[1m"+attacker->query_cap_name()+" flies "+
				"into a vicious tornado of motion, ripping apart "+victim->query_cap_name()
				+"![0m\n",
				({ attacker, victim }));
		victim->receive_damage(dam, attacker, TO->query_type());
		return 1;
	}
	return 0;
}
