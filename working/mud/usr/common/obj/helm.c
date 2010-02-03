inherit "/usr/System/lib/armor";

void create(varargs int clone){
    set_short(ESC+"[34mindigo helm"+ESC+"[0m");
    set_long(wrap("This is a helm for an indigo set.\n", 72));
    set_id( ({ "helm", "indigo helm" }) );
    set_type("helm");
    set_slot("head");
    set_ac(5);
    set_weight(10);
    set_bulk(20);
}
