/************************************
 *           combat.c               *
 * Any combative souls must inherit *
 * this                             *
 * NOTE: subscribe to event of      *
 * target dying                     *
 ************************************/
#define MY_HIT 	"You " + verbage[0] + " " + target_name + " with your " + weapon_short + " and " + dam_mess[0] + "\n"

#define  O_HIT 	attacker_name + " " + verbage[1] + " " + target_name + " with " + attacker_possessive + " " + weapon_short + " and " + dam_mess[1] + "\n"

#define  T_HIT 	attacker_name + " " + verbage[1] + " you with " + attacker_possessive + " " + weapon_short + " and " + dam_mess[1] + "\n"

#define MY_MISS "You attack " + target_name + " with your " + weapon_short + " and miss!\n"

#define  O_MISS attacker_name + " attacks " + target_name + " with " + attacker_possessive + " " + weapon_short + " and misses.\n"

#define  T_MISS attacker_name + " attacks you with " + attacker_possessive + " " + weapon_short + " and misses you!\n"

private static object *attackers;	/* array of attackers, check for combat */
private static int blocked_attacks; /* number of rounds to sit out */

int attack(object target);  /* proto */

int query_is_attackable(){ return 1; } /* may be unncessary */

int query_is_attacking(object ob){
	if(!attackers) attackers = ({});
	return (member_array(ob, attackers)>-1);
}

int query_in_combat(){/* determine if this cat is in combat */
	if(!attackers || sizeof(attackers) == 0){
		attackers = ({});
		blocked_attacks = 0;
		return 0;
	}
	return 1;
}

object *query_attackers(){ return attackers[..]; } /* may */

/****************************
 * returns target object or *
 * nil                      *
 ****************************/
object query_target(){
	int i, x;
	object room;
	if(!attackers){
		attackers = ({});
		return nil;
	}
	i = sizeof(attackers);
	room = this_object()->query_environment();
	if(!room) return nil; /* no room */
	for(x=0;x<i;x++){
		if(room->object_present(attackers[x]))return attackers[x];
	}
	return nil;/* no attacker in room */
}

int query_offhand(){/* whether to launch an offhand attack */
	mixed i;
	catch(i = this_object()->query_secondary());
	if(i && i != 1 && random(2)){/* to be made a function of body later */
		return 1;
	}
	return 0;
}

/******************
 * the actual hit *
 ******************/
void do_hit(object attacker, object attacked, object weapon, string attacker_name,
			string target_name, string attacker_possessive){
	string weapon_short, *verbage, *dam_mess;
	int damage;
	weapon_short = weapon->query_weapon_name();
	verbage = weapon->query_verbage();
	damage = weapon->query_damage()
			 + (attacker->query_stat("strength") * 2)
			 - random(attacked->query_stat("constitution"));
	if(damage < 1) damage = 1;
	switch(damage){
	case 0..5:
		dam_mess = ({ "hit wimpishly.", "hits wimpishly." });
		break;
	case 6..12:
		dam_mess = ({ "strike surely.", "strikes surely." });
		break;
	case 13..20:
		dam_mess = ({ "hit softly.", "hits softly." });
		break;
	case 21..40:
		dam_mess = ({ "hit solidly.", "hits solidly." });
		break;
	case 41..60:
		dam_mess = ({ "hit critically!", "hits critically!" });
		break;
	default:
		dam_mess = ({ "lay waste!", "lays waste!" });
		break;
	}
	attacker->catch_tell( MY_HIT );
	attacked->catch_tell( T_HIT );
	attacker->query_environment()->room_tell( O_HIT, ({ attacker, attacked }));
	attacked->receive_damage( damage, attacker, weapon->query_type() );

	catch{
		attacked->attack( attacker );
		if(attacker->query_environment()->object_present(attacked)){
			call_other( weapon, weapon->query_hit_func(), attacker, attacked );
		}
	}
	/* possibly add in armor specials */
}

/******************
 * the miss       *
 ******************/
void do_miss(object attacker, object attacked, object weapon, string attacker_name,
			string target_name, string attacker_possessive){
	string weapon_short;
	weapon_short = weapon->query_weapon_name();

	attacker->catch_tell( MY_MISS );
	attacked->catch_tell( T_MISS );
	attacker->query_environment()->room_tell( O_MISS, ({ attacker, attacked }));
}

int hit_roll(object weapon, varargs object body){
	int roll;

	roll = 0;
	if(body){
		roll += (body->query_stat("dexterity") * 2);
		roll += body->query_stat("strength");
	}
	roll += random(100) + weapon->query_accuracy();
	return roll;
}

/*******************************************
 * Round logic -                           *
 * -check for attackers                    *
 * -if so, check if attack [0] is with us  *
 * -if not, attack 1 and so on until found *
 * -check weapons, if none, attack with    *
 * default                                 *
 * -do attacks with primary                *
 * -check for possible secondary           *
 * -invoke specials on both weapons        *
 *******************************************/
int execute_attack(varargs int number){/* number is number of attacks to execute, default 1 */
	int target_ac, this_attack;
    string attacker_name, attacker_possessive, verb, target_name;
    object ta, primary, secondary, target;
	target = query_target();
	if(target == nil)return 0;/* nothing to attack */
	/*if(attackers[attack_num]->query_health() < 0)return 0;*/

	ta = this_object();
	attacker_name = ta->query_cap_name();
	target_name   = target->query_cap_name();
	attacker_possessive = ta->query_possessive();
	target_ac = target->query_ac();

	do{/* attack loop */
		catch(primary = ta->query_primary());
		if(primary){
			/*this_attack = random(primary->query_accuracy());
			this_attack += random(100);*/
			if(hit_roll(primary, ta) > target_ac){/* register hit */
				do_hit(ta, target, primary, attacker_name,
					   target_name, attacker_possessive);
			}else{/* register miss */
				do_miss(ta, target, primary, attacker_name,
					   target_name, attacker_possessive);
			}
		}else{/* attack with body */
			/*this_attack = random(ta->query_accuracy());
			this_attack += random(25);*/
			if(hit_roll(ta) > target_ac){/* needs to handle defaults */
				do_hit(ta, target, ta, attacker_name,
					   target_name, attacker_possessive);
			}else{
				do_miss(ta, target, ta, attacker_name,
						target_name, attacker_possessive);
			}
		}
		if(query_offhand() && ta->query_environment()->object_present(target)){
			secondary = ta->query_secondary();
			/*this_attack = random(secondary->query_accuracy());
			this_attack += random(100);*/
			if(hit_roll(secondary, ta) > target_ac){/* register hit */
				do_hit(ta, target, secondary, attacker_name,
				       target_name, attacker_possessive);
			}else{/* register miss */
				do_miss(ta, target, secondary, attacker_name,
				       target_name, attacker_possessive);
			}
		}
	}while( --number > 0 && ta->query_environment()->object_present(target));
	/*ta->catch_tell("hp: [ "+TO->query_health()+" / "+TO->query_max_health()+" ]\n\n");*/

	return 1;
}

/********************
 * initiate process *
 * values:          *
 * 1-attacked       *
 * 2-reattacked     *
 * 0-not possible   *
 ********************/
int attack(object target){
	int i;
	object temp;
	if(!attackers) attackers = ({});
	i = member_array(target, attackers);
	if(i == 0)return 2;
	if(i < 0){/* add him */
		if(sizeof(attackers) > 0){
			attackers += ({ attackers[0] });
			attackers[0] = target;
		}else{
			attackers += ({ target });
		}
		/* so he gets precedance */

		return 1;
	}
	/* guess he's a member, move to front */
	temp = attackers[0];
	attackers[0] = attackers[i];
	attackers[i] = temp;
	return 2;
}

/***********************************
 * routine to block normal attacks *
 ***********************************/
void block_attack(varargs int number){/* number is number of attacks to block, default 1 */
	if(number < 1) number = 1;
	if(number > blocked_attacks){
		blocked_attacks = number;
	}
}

int unblock_attack(varargs int number){/* and reversage */
	if(number < 1) number = 1;
	blocked_attacks -= number;
	if(blocked_attacks < 0){
		blocked_attacks = 0;
	}
}

/******************************
 * returns whether there's an *
 * attack that round          *
 ******************************/
int round_resolution(){/* called each round before attacks are launched */
	if(blocked_attacks > 0){
		blocked_attacks--;
		return 0; /* no authorized attack this round */
	}
	return 1; /* attack authorized */
}

void clean_attacker_not_in_room(){
	int i;
	object room;
	if(!attackers) attackers = ({});
	room = this_object()->query_environment();
	if(!room){
		attackers = ({});
		return;
	}
	i = sizeof(attackers);
	while(--i >= 0){
		if(!room->object_present(attackers[i])) attackers -= ({ attackers[i] });/* may be wrong */
	}
	if(sizeof(attackers) == 0)this_object()->catch_tell("Combat ends.\n");
}

void stop_attacking(object obj){
	int i;
	i = member_array(obj, attackers);
	if(i < 0)return;
	attackers -= ({ attackers[i] });
	if(sizeof(attackers) == 0){
		blocked_attacks = 0; /* we receive our actions back */
	}
}