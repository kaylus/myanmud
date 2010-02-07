/* ice */

inherit OBJECT;

void create(){
	add_command("preserve", "preserve");
	set_short("[36;1mice[0m");
	set_long("This ice can be used to preserve limbs.\n");
	set_id( ({ "ice" }) );
}

int preserve(string str){
	object limb;
	string thing;

	if(!str) return fail_msg("Preserve what?\n");

	limb = TP->present(str);
	if(!limb || !limb->is_limb()) return fail_msg("Preserve what?\n");

	limb->stop_decay();
	write("You put the limb on ice.\n");
	say(TPN+" puts the limb on ice.\n");
	call_out("destruct", 0);
	return 1;
}