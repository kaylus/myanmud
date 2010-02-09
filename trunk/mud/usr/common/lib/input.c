/*
 * souls use this to do body commands 
 */
 
# include <type.h>
/* input command decipherer */
int input(string str){
    string cmd, args, fail_msg;
    mixed ret_fail;
    object *inv, user;
    fail_msg = "";

    if(sscanf(str, "%s %s", cmd, args) < 2){
	cmd = str;
	args = "";
    }

    /* do some alias stuff */
	user = this_object()->query_user();/* TODO: make this more accessible to non usered bodies */
    if(user->query_alias(cmd) != cmd && (!user->query_wiztool() || !query_editor(user->query_wiztool()))){/* found alias */
	string argx;
	cmd = user->query_alias(cmd);
	if(sscanf(cmd, "%s %s", cmd, argx) > 0){/* have args */
	    args = argx + args;
	}
    }

    /* return is as follows
	 *  1 - action done, end command search
	 *  nil - continue seek
	 *  string - fail string, continue seek
     */

    /* body bin, make this a loop */

    /* channeld check */
    catch{
	if(find_object(CHANNELD)->cmd_channel(cmd, args) == 1) return 1;
    }

    if (file_info(BODY_BIN+"cmd_" + cmd+".c") != nil || (cmd=="help" && file_info(BODY_BIN+"cmd_"+args+".c") != nil)){/* found a bin command, or help on args */
	if (cmd=="help"){
		cmd = args;
		args = "-h";
	}
	if(!find_object(BODY_BIN+"cmd_"+cmd))compile_object(BODY_BIN+"cmd_"+cmd);/* load if it isn't loaded */
	catch(ret_fail = find_object(BODY_BIN+"cmd_"+cmd)->do_cmd(cmd, args, this_object()));/* change to call_limited? */
	}
	
    switch(typeof(ret_fail)){
    case T_STRING:/* fail string, continue seek */
	fail_msg = ret_fail;
    case T_NIL:/* continue seek */
	break;
    default: /* done */
	return 1;
    }

    /* other bins... */
    /* room/body inventory bin */
    /* error checking */
    inv = ({});
    if(this_object()->query_environment()){ 
	inv += ({ this_object()->query_environment() });
	if(this_object()->query_environment()->query_inventory()) 
	    inv += this_object()->query_environment()->query_inventory();
    }

    if(this_object()->query_inventory())
	inv += this_object()->query_inventory();

    inv -= ({ this_object() });

    if(sizeof(inv)){
	int i;
	i = sizeof(inv);
	while(--i>=0){

	    if(function_object("perform_action", inv[i]))
		ret_fail = call_other(inv[i], "perform_action", cmd, args);

	    switch(typeof(ret_fail)){
	    case T_STRING:/* fail string, continue seek */
		fail_msg = ret_fail;
	    case T_NIL:/* continue seek */
		break;
	    default: /* done */
		return 1;
	    }
	}
    }
	
	if(this_object()->query_environment() && this_object()->query_environment()->query_exit(str) && file_info(BODY_BIN+"cmd_go.c") != nil){
		cmd = "go";
		if(!find_object(BODY_BIN+"cmd_"+cmd))compile_object(BODY_BIN+"cmd_"+cmd);/* load if it isn't loaded */
		ret_fail = find_object(BODY_BIN+"cmd_"+cmd)->do_cmd(cmd, str, this_object());
		switch(typeof(ret_fail)){
	    case T_STRING:/* fail string, continue seek */
		fail_msg = ret_fail;
	    case T_NIL:/* continue seek */
		break;
	    default: /* done */
		return 1;
	    }
	}

    if(!strlen(fail_msg))
	return 0;

    this_object()->message(fail_msg);/* failed to find command */
    return 1;
}
