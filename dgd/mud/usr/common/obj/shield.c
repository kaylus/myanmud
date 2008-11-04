/* test subject */

inherit "/usr/System/lib/armor";

void create(varargs int clone){
    set_short(ESC+"[1ma coruscant shield"+ESC+"[0m");
    set_long("This shield shines brightly, illuminating its owner with its brightness.\n");
    set_id( ({ "shield", "coruscant shield" }));
    set_type("shield");
    set_slot("arm");
    set_ac(10);
    set_weight(10);
    set_bulk(20);
}

