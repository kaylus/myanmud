/*
   look.c
   The basic look command.
   Written by Mobydick, 5-26-94.
*/

int do_command(string str){
    string arg;
    object env, thing;

    /* Can we see? */
    if(!TP->query_vision()){
	write("It is dark and you can't see a thing.\n");
	return 1;
    }

    if(str && sscanf(str, "in %s", arg))/* let this pass up to container */
	return fail_msg("look [in] <container>\n");

    if(!str)
	str = "";
    /* Was an argument passed? If so, find an object that matches that
       string and return its long description.
       Hymael - made it play nicer
       Eliminated need for at syntax
       Possible future problem with compound names
       but for now it works
       Working for compound names
     */
    if(sscanf(str, "at %s", arg) || sscanf(str, " %s", arg) || (arg = str)){
	/* If no argument was passed, then we're looking in our room. */
	env = TP->query_environment();
	if(!arg || replace_string(arg, " ","") == ""){
	    if(!env){
		write("You are in the void and can see nothing.\n");
		return 1;
	    }
	    write(env->query_long());
	    return 1;
	}
	thing = env->present(arg);
	if(thing){
	    write(thing->query_long());
	    return 1;
	}
	thing = TP->present(arg);
	if(thing){
	    write(thing->query_long());
	    return 1;
	}
	write("I don't see "+article(arg)+" "+arg+" here.\n");
	return 1;
    }
    /* Give up. */
    return 0;
}

string help(){
    return "Usage: look [at] <object>\n\n\
This is the fundamental look command.";
}
