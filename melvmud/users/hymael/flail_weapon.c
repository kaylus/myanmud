/* realm's first weapon */

#include <config.h>
#define CHANCE 15

inherit WEAPON;
inherit container CONTAINER;

void create() {
    set_short ("[31man insidious flail[0m") ;
    add_command("strike", "strike") ;
    set_long (wrap("The flail writhes as though it is alive. It demands that you \
strike someone.  You feel the overwelming urge to slay.\n",72)) ;
    set_id ( ({ "flail", "a flail" }) ) ;
    set_type ("cut");
    set_accuracy (20);
    set_damage ( ({ 3, 4 }) );
    set_hit_func ("special");
    set_wield_func ("wield");
    set_unwield_func ("unwield");
   	set_verbs_me (({ "crush", "crunch", "strike" }));
   	container::create();
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
int strike (string str) {
	object strikee;
	if(!str)return fail_msg("The flail moans for flesh.\n");
	strikee = ETP->present(str);
	if(!strikee || !strikee->query_living())
		return fail_msg("The flail finds no one by that name.\n");
	/* message up some death */
	write("[30m[1mThe flail sinks into "+capitalize(str)+"'s flesh, delving deep and \
scoring devilish wounds![0m\n");
	strikee->catch_tell("[30m[1m"+TPN+"'s flail sinks into your flesh, delving for your \
very marrow![0m\n");
	say("[30m[1m"+TPN+"'s flail sinks into "+capitalize(str)+"'s flesh![0m\n", ({ strikee }));
	strikee->receive_damage(random(15), TP);
	return 1 ;
}

int special (object attacker, object attacked){
	int dam;
	switch(random(100)){/* check to special */
	case 0..CHANCE:
		dam = random(15)+1;
		attacker->catch_tell("The flail goes to work on "+
			attacked->query_cap_name()+"'s [31mflesh[0m!\n");
		attacked->catch_tell(attacker->query_cap_name()+"'s flail goes to work "+
			"on your [31mflesh[0m!\n");
		attacker->query_environment()->room_tell(attacker->query_cap_name()+"'s flail "+
			"goes to work on "+attacked->query_cap_name()+"'s [31mflesh[0m!.\n",
			({ attacker, attacked }));
		attacked->receive_damage(dam, attacker, TO->query_type());
		return 1;
	}
	/* nothing special this round */
	return 0;
}
