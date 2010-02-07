/* steel */

inherit "/inherit/tradeskills/component.c";

create(){
        set_tradeskill("weaponsmithing");
        set_short("steel");
        set_long("This is steel, very potent.\n");
        set_alloy("pig iron");
        set_bonus(100);
        set_difficulty(40);
        set_subset("alloy");
        set_color("");
        set_id( ({ "steel" }) );
        set_weight(5);
        set_bulk(1);
}
