/* ebow */

#include <config.h>
#define CHANCE 45

inherit "/inherit/weapon.c";

void create() {
    set_short ("[1mEnergy Crossbow[0m") ;
    set_long (wrap("This hand crossbow appears to be made of fine quality wood.  The small \
size of this weapon makes you disbelieve its destructive nature.  There \
are several runes engraved on the grip, but you are unable to read them.\
\n",72)) ;
    set_id ( ({ "energy bow", "bow" }) ) ;
    set_type ("missile");
    set_accuracy (15);
    set_damage ( ({ 7, 15 }) );
    set_hit_func ("special");
   	set_verbs_me (({"attack","fire at","shoot at"}));
	set_verbs_other(({"attacks","fires at","shoots at"}));
}

int special(object attacker, object victim){
  	int which_special, chance, dam;
  	string aname, vname;
  	chance = random(50);
  	dam = 0;


    if (chance <= 10) {
        which_special = random(3) + 1;
        aname = attacker -> query_cap_name();
        vname = victim -> query_cap_name();
        switch (which_special) {
        case 1 :
            victim->catch_tell(
              "   [33m[1mA bolt of golden energy comes from the bow and wraps around\n"+
              "   your body!  You struggle to free yourself.[0m\n");
            attacker->catch_tell(
              "   [33m[1mA bolt of golden energy comes from your bow and wraps around[0m\n"+
              "   "+vname+"'s [33m[1mbody![0m\n");
            attacker->query_environment()->room_tell(
              "   [33m[1mYou watch as a bolt of golden energy flies from the bow\n"+
              "   and wraps around[0m "+vname+"'s [33m[1mbody![0m\n",({attacker, victim}));

            dam = 4 + random(6);
            victim -> block_attack(dam);
            return(1);
            break;
        case 2 :
            victim->catch_tell(
              "   [34mA bluish beam streaks from the bow and strikes you in the chest!\n"+
              "   Your body shudders as electricity wreaks havoc on your system.[0m\n");
            attacker->catch_tell(
              "   [34mA bluish beam streaks from your bow and strikes[0m\n"+
              "   "+vname+" [34min the chest!   You watch as electricity dances\n"+
              "   up and down [0m"+vname+"'s [34mbody.[0m\n");
            attacker->query_environment()->room_tell(
              "   [34mA bluish beam streaks from [0m"+aname+"'s [34mbow\n"+
              "   and strikes [0m"+vname+" [34min the chest![0m\n",({attacker, victim}));

            dam = 20 + random(15);
            victim -> receive_damage(dam,attacker,"electricity");
            break;
        case 3 :
           	attacker->catch_tell(
              "   [31mA beam of crackling red energy flies from the bow and strikes[0m\n"+
              "   "+vname+" [31min the chest![0m\n");
            victim->catch_tell(
              "   [31mA burning hot beam of energy strikes your body!  You scream in agony\n"+
              "   as you feel it start to burn away at your skin.[0m\n");
            attacker->query_environment()->room_tell(
              "   [31mA beam of crackling red energy flies from [0m"+aname+"'s[31m\n"+
              "   bow and strikes [0m"+vname+"'s [31mbody.[0m\n",({attacker,victim}));

            dam = 15 + random(25);

            victim -> receive_damage(dam,attacker,"fire");
            break;
        }
    }
}