/* iceblade.c */

#include <config.h>
#define CHANCE 10

inherit WEAPON;

void create() {
    set_short ("[1m[36ma crystal blade[0m") ;
    set_long (wrap("Translucent, this blade looks as if it is made of crystal. \
It is light in weight and cold to touch. You fear that it would melt in a heated \
combat.\n",72)) ;
    set_id ( ({ "blade", "crystal bladel" }) ) ;
    set_type ("thrust");
    set_accuracy (50);
    set_damage ( ({ 20, 10 }) );
    set_hit_func ("special");
    set_wield_func ("wield");
    set_unwield_func ("unwield");
        set_verbs_me (({ "thrust", "slash", "pierce" }));
        set_offhand();
}

int wield(){
        write(wrap("You grab the hilt of the blade and it starts melting in your \
hand only to freeze again and hold your hand fast in this icy bond. \n",72));
        return 0;
}

int unwield(){
	        write(wrap("You loosen your grip on the blade, and yet, the hilt of \
blade is not damaged by the heat of your hand and the battle.\n",72));
	        return 0;
}

int special (object attacker, object attacked){
	        int dam;
	        switch(random(50)){
        case 0..CHANCE:
                   dam = random(50)+1;
	                attacker->catch_tell(wrap("The blade melts on "+
attacked->query_cap_name()+"'s body, then freezes again, ripping off a large \
piece of flesh exposing the internals!\n", 72));
	                attacked->catch_tell(wrap(+attacker->query_cap_name()+"'s \
blade melts and re-freezes, opening up a big hole on your body!\n", 72));
	                attacker->query_environment()->room_tell(wrap(+attacker->query_cap_name()+
	                "'s blade freezes up and tears off a piece of flesh \
off "+attacked->query_cap_name()+"'s body!\n",72), ({ attacker, attacked }));
	                 return 1;
}
	        return 0;
}
