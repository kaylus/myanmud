/* smirs_sword.c
    weapon to mock Hymael*/

#include <config.h>

inherit WEAPON;

void create() {
    set_short ("[1m[32mSword of Smirs[0m") ;
    set_long (wrap("A shortsword forged by the crazee woman Sileas. It is \
dedicated to Hymael and his smirs.\n",72)) ;
    set_id ( ({ "sword", "shortsword", "sword of smirs" }) ) ;
    set_type ("cut");
    set_accuracy (50);
    set_damage ( ({ 20, 10 }) );
    set_verbs_me (({ "cut", "slash", "chop", "smir" }));
    set_verbs_other (({ "cuts", "slashes", "chops", "smirs" }));
    set_offhand();
    set_wield_func ("wield");
    set_unwield_func ("unwield");
 }
     
     int wield(){
        write(wrap("You feel the urge to smir when you wield the sword.\n",72));
        say(wrap(TPN+" starts smir'ing.\n", 72));
        return 1;
}
    	
    int unwield(){
        write(wrap("You stop smir'ing as you unwield the sword.\n",72));
        say(wrap(TPN+" stops smir'ing.\n",72));
        return 1;
}
