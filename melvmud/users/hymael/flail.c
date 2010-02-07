/* damage dealer */

#include <config.h>

inherit OBJECT ;

void create() {
    set_short ("[31man insidious flail[0m") ;
    add_command("strike", "strike") ;
    set_long (wrap("The flail writhes as though it is alive. It demands that you \
strike someone.  You feel the overwelming urge to slay.\n",72)) ;
    set_id ( ({ "flail" }) ) ;
}

int strike (string str) {
	object strikee;
	if(!str)return fail_msg("The flail moans for flesh.\n");
	strikee = ENV->present(str);
	if(!strikee || !strikee->query_living())
		return fail_msg("The flail finds no one by that name.\n");
	/* message up some death */
	write("[30m[1mThe flail sinks into "+capitalize(str)+"'s flesh, delving deep and \
scoring devilish wounds![0m\n");
	strikee->catch_tell("[30m[1m"+TPN+"'s flail sinks into your flesh, delving for your \
very marrow![0m\n");
	say("[30m[1m"+TPN+"'s flail sinks into "+capitalize(str)+"'s flesh![0m\n", ({ strikee }));
	strikee->receive_damage(random(15), TP);
	return 1 ;
}
