/* draining flail */

#include <config.h>
#define CHANCE 19

inherit WEAPON;

void create() {
    set_short ("[32m[1ma thirsty flail[0m") ;
    set_long (wrap("The flail writhes as though it is alive. It demands that you \
strike someone.  You feel the overwelming urge to slay.\n",72)) ;
    set_id ( ({ "flail", "thirsty flail" }) ) ;
    set_type ("cut");
    set_accuracy (70);
    set_damage ( ({ 20, 4 }) );
    set_hit_func ("special");
    set_wield_func ("wield");
    set_unwield_func ("unwield");
   	set_verbs_me (({ "crush", "crunch", "strike" }));
   	set_offhand();
}

int wield(){
	write(wrap("You feel the flail's insidious tines bite into your hand as you heft it!\n",72));
	say(wrap(TPN+" wields the flail and you catch of glimpse of the insidious weapon's tortured \
past.\n", 72));
	return 1;/* denotes messages handled */
}

int unwield(){
	write(wrap("You feel the killing rage abate as you put the flail away.\n",72));
	say(wrap(TPN+" puts the flail away, losing much of "+TP->query_possessive()+" \
imposing demeanor.\n",72));
	return 1;
}

int special (object attacker, object attacked){
	int dam;
	switch(random(100)){/* check to special */
	case 0..CHANCE:
		dam = random(20)+1;
		attacker->catch_tell(wrap("[32m[1mThe flail goes to work on "+
			attacked->query_cap_name()+"'s flesh, you feel their health drain into you![0m\n", 72));
		attacked->catch_tell(wrap("[32m[1m"+attacker->query_cap_name()+"'s flail goes to work "+
			"on your flesh, you feel the devious weapon drain away your life![0m\n", 72));
		attacker->query_environment()->room_tell(wrap("[32m[1m"+attacker->query_cap_name()+"'s flail "+
			"goes to work on "+attacked->query_cap_name()+"'s flesh![0m\n",72),
			({ attacker, attacked }));
		attacker->receive_healing(dam);
		attacked->receive_damage(dam, attacker, TO->query_type());
		return 1;
	case CHANCE+1..CHANCE+7:
		dam = random(40)+1;
		attacker->catch_tell(wrap("[31m[1mThe flail thrashes about, skewering "+
				  attacked->query_cap_name()+"'s face and temporarily stunning "+
				  attacked->query_objective()+"![0m\n", 72));
		attacked->catch_tell(wrap("[31m"+attacker->query_cap_name()+"'s flail thrashes about "+
				  "striking you in the face and stunning you![0m\n", 72));
		attacker->query_environment()->room_tell(wrap("[31m"+attacker->query_cap_name()+"'s flail "+
				  "thrashes "+attacked->query_cap_name()+"'s face![0m\n",72),
				  ({ attacker, attacked }));
		attacked->receive_damage(dam, attacker, TO->query_type());
		attacked->block_attack(random(5)+1);
		return 1;
	}
	/* nothing special this round */
	return 0;
}
