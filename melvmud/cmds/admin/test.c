#include <config.h>
#include <status.h>
#include <body.h>
#include <type.h>


int do_command (string str) {
	int a, b, c, x, i;
	string d, e, f, *log, *indies;
	object g, h;
	mapping z;
	mixed *aray;
	mixed **clist;

#if 0

	g = find_object("inherit/ship");
	"system/sea_d"->ship_enter(({ 0, 5 }));



 	write("test?");
#endif
	h = USERS_D->find_user(lowercase(str));
	if(!h)
		return fail_msg("No player by that name.\n");

	h = h->query_player();
	if(!h)
		return fail_msg("User has no body.\n");

	clist = status(h)[O_CALLOUTS];
	i = sizeof(clist);
	write(h->query_cap_name()+" Callouts: \n");
	while(i--){
		write("Name: "+clist[i][CO_FUNCTION]+" Delay: "+clist[i][CO_DELAY]+" Arg: ");
		if(sizeof(clist[i]) > CO_FIRSTXARG){
			if(typeof(clist[i][CO_FIRSTXARG]) == T_OBJECT){
				write(object_name(clist[i][CO_FIRSTXARG]));
			}else{
				write((string)clist[i][CO_FIRSTXARG]);
			}
		}
		write("\n");
	}
#if 0

	h = USERS_D->find_user(lowercase(str));
	if(!h)
		return fail_msg("No player by that name.\n");

	h = h->query_player();
	if(!h)
		return fail_msg("User has no body.\n");

	h->save_object("/log/datatmp");
	write(h->query_cap_name()+"'s DATA:\n\n"+read_file("/log/datatmp")+"\n");


	i = status()[O_CALLOUTS][CO_DELAY];
	write((string)i+"\n");

	/*write((string)(floor
		(80-
		(80.0
		*
		exp(
			(-1.0*(float)((
				(float)
				200.0
				)
				/
				85.0))
				)))));*/
	/*write((string)floor(80.0 -
	                    exp(-85.0/85.0)));*/
	write((string)(floor(8.0 - log(200.0 + 2.0))));

		to_int(floor(80-(80*exp(-to_float(tmp)/85.0))));
#endif
#if 0
	write("containing\n");
	{
		string ninny;
		ninny = "contained";
		write(ninny+"\n");
	}

 	write("\
 |\n\
 |  | |\n\
||\\/----\n\
 |    |\n\
 |  ----\n\
 |    |\n\
 | ___|__\n");
 	say("\
 |\n\
 |  | |\n\
||\\/----\n\
 |    |\n\
 |  ----\n\
 |    |\n\
 | ___|__\n");




	log_file(HB_LOG, "Error: primed pump\n");

	g = TP->query_environment()->present(str);
		g->add_malignancy("head", -1, 4, "cold", "throbs", "left arm");
		write(g->query_cap_name()+"\nMaligs:\n");
	write(g->print_maligs()+"\n");

	aray = ({});
	aray += ({ ({ 1, 2, 3 }) });
	aray += ({ ({ 11, 22, 33 }) });
	i = sizeof(aray);
	while(i--){
		write(aray[i][0]+"\n");
	}
	g = TP->query_environment()->present(str);
	g->add_malignancy("head", -1, 4, "cold", "throbs", "left arm");
	write(g->query_cap_name()+"\nMaligs:\n");
	write(g->print_maligs()+"\n");

	z = BODY_PARTS;

	indies = map_indices(z);
	x = sizeof(indies);
	while(x--){
		write(pad(indies[x],10)+" -> "+z[indies[x]]+"\n");
	}
	indies = BP_ALL;
	x = sizeof(indies);
	while(x--){
		write(indies[x]+"\n");
	}

	g = USERS_D->find_user("sileas");
	/*g = g->query_player();*/
	if(!g)return fail_msg("Player not found.\n");
	log = g->query_saybacklog();
	if(!log)return fail_msg("No log.\n");
	i=sizeof(log);
	for(x=0;x<i;x++)write(log[x]);
	/*g = g->query_player();/* note of this */
	/*h = clone_object("/obj/squid");
	if(!h)return fail_msg("Clone failed.\n");
	a = h->move(g);
	if(!a)return fail_msg("Move failed.\n");
	write("You send "+g->query_cap_name()+" "+h->query_short()+".\n");
	g->catch_tell("You receive "+h->query_short()+" from "+TPN+".\n");*/
	/*i = status();*/
	/*write(status()[ST_NCOSHORT][CO_HANDLE]+"\n");*/

	/*for(a=30;a<47;a++){
		write("["+a+"mTest\n");
		write("[1mTest[0m\n");
		say("["+a+"mTest\n");
		say("[1mTest[0m\n");
	}*/
	/*h= USERS_D->find_user(lowercase(str));
	h=h->query_player();
	write(h->query_cap_name()+"\n");
	/*h->catch_tell("A squid drops into your hands by the will of [1mHymael.\n[0m");
	write(h->query_name()+" got the squid.\n");
	/*write("[43mTest\n[0m");
	write("You [1mhug[0m Sileas!\n");
	say("Hymael [1mhugs[0m you!\n");*/
	/*g=TP->query_environment()->present("igor");
	write(g->query_name()+"\n");
	g->do_command(str);*/
#endif

	return 1 ;
}
