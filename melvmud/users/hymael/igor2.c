/* Test monster */

inherit MONSTER;

void create() {
	::create();
    set_short ("Igor") ;
    set_long ("Igor, the brain-toting wonder monster.\n") ;
    set_id ( ({ "igor" }) ) ;
    enable_commands();
    set_gender("male");
    set_damage(({ 40, 30 }));
    set_accuracy(50);
    set_verbs_me(({ "slash", "strike", "cut" }));
    set_verbs_other(({ "slashes", "strikes", "cuts" }));
	set_weapon_name("claws");
	set_follow();

}

