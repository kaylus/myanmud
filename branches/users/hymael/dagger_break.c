/* realm's second weapon */

inherit "/inherit/weapon2.c";

void create() {
    set_short ("[35mindigent dagger[0m") ;
    set_long (wrap("This dagger appears as a pathetic instrument.  But its heft is \
impeccable.  You feel as though it could tear through sinew with ease.\n",72)) ;
    set_id ( ({ "dagger", "indigent dagger" }) ) ;
    set_type ("cut");
    set_accuracy (30);
    set_quality(-100);
    set_damage ( ({ 7, 10 }) );
   	set_verbs_me (({ "strike", "slash" }));
   	set_verbs_other (({ "strikes", "slashes" }));
   	set_offhand();
}
