/* The clone command. Take a filename, clone a copy of it, and move it
   to the cloning wizard's inventory.
   Written by Mobydick, 7-13-94
*/

#define SYNTAX "Usage: clone <filename>\n"

int do_command (string file) {

    object ob ;
    /*int res ;*/
    string res;

    if(!file){
		file = TP->query_cwf();
		if(!file)
      		return fail_msg (SYNTAX);
    }
    if (!absolute_path(file)) file = TP->query_cwd()+file ;
    file = resolve_path(file) ;
    if (file[strlen(file)-2..strlen(file)-1]!=".c") file += ".c" ;
    if (file_exists(file)<1) {
        write ("No such file: "+file+"\n") ;
	return 1 ;
    }
/* First, ob is the master object (get_object() loads it if that is
   necessary), then ob becomes the new clone.
*/
    ob = get_object(file) ;
    ob = clone_object(ob) ;
    if (!ob) {
        write ("Failed to clone "+file+"\n") ;
	return 1 ;
    }
    res = catch(ob->move(TP)) ;
    if (res) {
        write ("Could not move object to your inventory.\n") ;
		res = catch(ob->move(TP->query_environment()));
		if (res) {
	    	write ("Could not move it to your environment. Aborting clone.\n");
	    	return 1 ;
		}
		write(file+" cloned to your environment.\n") ;
		say(TPN+" creates "+ob->query_short()+
	                  ".\n") ;
	return 1 ;
    }
    write (file+" cloned.\n") ;
    say(TPN+" creates "+ob->query_short()+".\n") ;
    return 1 ;
}

string help(){
	return SYNTAX+"\n\
The clone command. Take a filename, clone a copy of it, and move it\n\
to the cloning wizard's inventory.\n";
}