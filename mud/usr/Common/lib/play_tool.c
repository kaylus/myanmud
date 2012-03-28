/* player interface commands, may make this an object and directable to a body,
   that way command interfaces can change between players */
#include <game/weight.h>

#define PREFIX "cmd_"		/**< added to the functions */
#define USER this_object()->query_user()	/**< temp */
#define BEEP ""
/* all commands will return a fail string or nil, signifying success */

/* return is as follows
	1 - action done, end command search
	nil - continue seek
	string - fail string, continue seek
 */



/** look function */
mixed cmd_look(string str){
    string arg;    


    #if 0
    /* Can we see? */
    if(!TP->query_vision()){
	write("It is dark and you can't see a thing.\n");
	return 1;
    }
    #endif

    if(str && sscanf(str, "in %s", arg))/* let this pass up to container */
	return "look [in] <container>\n";

    if(!str)
	str = "";
    
    if(str == "me" || str == "at me"){
        str = this_object()->query_name(); 
    }
    /* Was an argument passed? If so, find an object that matches that
     *        string and return its long description.
     *               Hymael - made it play nicer
     *                      Eliminated need for at syntax
     *                             Possible future problem with compound names
     *                                    but for now it works
     *                                           Working for compound names
     *                                                */
    if(sscanf(str, "at %s", arg) || sscanf(str, " %s", arg) || (arg = str)){
	object env, thing;

	/* If no argument was passed, then we're looking in our room. */
	env = this_object()->query_environment();
	if(!arg ||  implode(explode(" "+arg+" "," "),"") == ""){
	    if(!env){
		this_object()->message("You are in the void and can see nothing.\n");
		return 1;
	    }
	    this_object()->message(env->query_long());
	    return 1;
	}
	thing = env->present(arg);
	if(thing){
	    this_object()->message(thing->query_long());
	    return 1;
	}
	thing = this_object()->present(arg);
	if(thing){
	    this_object()->message(thing->query_long());
	    return 1;
	}
	this_object()->message("I don't see "+/*article(arg)*/"a"+" "+arg+" here.\n");
	return 1;
    }
    /* Give up. */
    return nil;
}

mixed cmd_test (string str)
{
    if (!strlen (str))
	return "Must put something after test.\n";

    this_object ()->message ("Tested.\n");

    return 1;
}

/** go in a direction */
mixed cmd_go (string str)
{
    object environ, dest;
    string err;

    environ = this_object ()->query_environment ();

    if (!environ)
	return "You must have an environment to leave from!\n";

    dest = environ->query_exit (str);
    if (!dest)
	return "You cannot go in that direction.\n";

    err = catch (this_object ()->move (dest, str));

    if (err)
	return err;

    return 1;
}

mixed
cmd_beep (string str)
{
    object person;

    if (!str || !strlen (str))
    {
	this_object ()->message (BEEP + "You beep.\n");
	this_object ()->query_environment ()->message (BEEP +
	  this_object ()->
	  query_Name () +
	  " beeps.\n", (
	  {
	    this_object
	    ()}
	));
	return 1;
    }

    person = this_object ()->query_environment ();

    if (!person)
	return "No one by that name to beep.\n";

    person = person->present (str);

    if (!person)
	return "No one by that name to beep.\n";

    this_object ()->message (BEEP + "You beep " + person->query_Name () +
      ".\n");
    this_object ()->query_environment ()->message (BEEP +
      this_object ()->
      query_Name () + " beeps " +
      person->query_Name () +
      ".\n", (
      {
	person,
	this_object ()}
    ));

    person->message (BEEP + this_object ()->query_Name () + " beeps you.\n");

    return 1;
}

mixed
cmd_kill (string str)
{
    object room, thing;
    string name, tname;

    if (!str)
	return "Usage: kill <person>\n";

    room = this_object ()->query_environment ();
    if (!room)
	return "Where are you?";

    thing = room->present (str);
    if (!thing)
	return "There is no " + str + " to attack.\n";

    if (!thing->query_is_attackable ())
	return "You cannot attack that.\n";

    if (thing == this_object ())
	return "You masochist.\n";

    tname = thing->query_Name ();
    name = this_object ()->query_Name ();
    switch (this_object ()->attack (thing))
    {
    case 1:
	name = this_object ()->query_Name ();
	this_object ()->message ("You attack " + tname + "!\n");
	this_object ()->query_environment ()->message (name + " attacks " +
	  tname + "!\n", (
	  {
	    this_object
	    (),
	    thing}
	));
	thing->message (name + " attacks you!\n");
	break;
    default:
	this_object ()->message ("You redouble your efforts against " + tname +
	  ".\n");
	break;
    }
    return 1;
}

mixed cmd_inventory(varargs string str){

    object *stuff;
    string name;
    int i, sz, p_cap, p_volume, max_volume, max_cap;

    p_cap = this_object()->query_p_cap();
    p_volume = this_object()->query_p_volume();
    max_cap = this_object()->query_capacity();
    max_volume = this_object()->query_volume();

    str = " Carried: ["+p_cap+" / "+max_cap+"] "+WEIGHT_UNIT+"s\n";

    stuff = this_object()->query_inventory();
    if(!stuff || !(sz=sizeof(stuff))){
	this_object()->message(str+"\nYou are empty-handed.\n");
	return 1;
    }
    for(i=0; i<sz; i++){
	name = stuff[i]->query_short();
	/* If it has no short it shouldn't show up in your inventory list. */
	if (!name || !strlen(name))
	    continue;

	str += "  "+capitalize(name)+"\n";
    }
    this_object()->message(str);
    return 1;
}

mixed cmd_wield(string str){
    object thing;

    if (!str || !strlen(str)) {
	return "Usage: wield <item>\n";
    }
    thing = this_object()->present(str);
    if (thing){

	if((str = catch(this_object()->wield(thing)))){
	    return str;
	}

	if(!thing->query_wield_func() || catch(call_other(thing, thing->query_wield_func()))){/* messages not handled */
	    this_object()->message("You wield "+thing->query_short()+".\n");
	    this_object()->query_environment()->message(this_object()->query_Name()+" wields "+thing->query_short()+".\n", ({ this_object() }));
	}
	return 1;
    }
    this_object()->message("No "+str+" to wield.\n");
    return 1;
}

mixed cmd_unwield(string str){
    object thing;


    if (!str || !strlen(str)) {
	return "Usage: unwield <item>\n";
    }
    thing = this_object()->present(str);
    if (thing){

	if((str = catch(this_object()->unwield(thing)))){
	    return str;
	}

	if(!thing->query_unwield_func() || catch(call_other(thing, thing->query_unwield_func()))){/* messages not handled */
	    this_object()->message("You unwield "+thing->query_short()+".\n");
	    this_object()->query_environment()->message(this_object()->query_Name()+" unwields "+thing->query_short()+".\n", ({ this_object() }));
	}
	return 1;
    }
    this_object()->message("No "+str+" to unwield.\n");
    return 1;
}

mixed cmd_equip(string str){
    object thing;

    if (!str || !strlen(str)) {
	return "Usage: equip <armor>\n";
    }
    thing = this_object()->present(str);
    if (thing){

	if((str = catch(this_object()->equip(thing)))){
	    return str;
	}

	if(!thing->query_equip_func() || catch(call_other(thing, thing->query_equip_func()))){/* messages not handled */
	    this_object()->message("You equip "+thing->query_short()+".\n");
	    this_object()->query_environment()->message(this_object()->query_Name()+" equips "+thing->query_short()+".\n", ({ this_object() }));
	}
	return 1;
    }
    this_object()->message("No "+str+" to equip.\n");
    return 1;
}

mixed cmd_unequip(string str){
    object thing;

    if (!str || !strlen(str)) {
	return "Usage: unequip <armor>\n";
    }
    thing = this_object()->present(str);
    if (thing){

	if((str = catch(this_object()->unequip(thing)))){
	    return str;
	}

	if(!thing->query_unequip_func() || catch(call_other(thing, thing->query_unequip_func()))){/* messages not handled */
	    this_object()->message("You unequip "+thing->query_short()+".\n");
	    this_object()->query_environment()->message(this_object()->query_Name()+" unequips "+thing->query_short()+".\n", ({ this_object() }));
	}
	return 1;
    }
    this_object()->message("No "+str+" to unequip.\n");
    return 1;
}

mixed cmd_hp(string str){
    this_object()->message("Status:"+this_object()->query_diagram());
    return 1;
}

mixed cmd_score(varargs string str){
    mapping stats;
    int i;
    string *attributes;

    stats = this_object()->query_stats();
    attributes = map_indices(stats);
    i = sizeof(attributes);

    str = this_object()->query_Name() + "\n";
    str += this_object()->query_diagram();

    while(i--){
	str += ESC+"[36;1m"+pad(capitalize(attributes[i])+": ", 15)+ESC+"[0m"+stats[attributes[i]]+"\n";
    }

    this_object()->message(str);
    return 1;
}

mixed cmd_skills(string str){
    this_object()->message(this_object()->query_skills());
    return 1;
}

mixed cmd_wealth(string str){
    this_object()->message(this_object()->query_wealth());
    return 1;
}

mixed cmd_get(string str){
    object thing, env;
    string s1, s2;
    int num;

    string res;

    if (!str || sscanf(str, "%s from %s", s1, s2) == 2)
	return "Usage: get all | <item> [from <container>]\n";

    env = this_player()->query_environment() ;
    if(!env) return "No environment.\n";

    if(str == "all"){/* get everything */
	int sz, i;
	object *things;

	things = env->query_inventory();
	if(!things || !(sz=sizeof(things))){
	    this_player()->message("Nothing to get.\n");
	    return 1;
	}
	while(sz--){
	    if(things[sz]->is_body() || things[sz]->prevent_get())
		continue;

	    i++;
	    res = catch(things[sz]->move(this_player()));
	    if(res){
		/* nothing for now */
	    }
	}
	if(i){
	    this_player()->message("You get everything.\n");
	}else{
	    this_player()->message("Nothing to take.\n");
	}
	return 1;
    }
    /***MONEY***/
    if(sscanf(str, "%d %s", num, s1) == 2 || sscanf(str, "%d %s coin", num, s1) == 2){
	string type;
	thing = env->present(s1);
	if(!thing || !thing->is_coins())
	    return "No money.\n";

	type = thing->query_cointype();
	str = catch(thing->coin_move(this_player(), num));
	if(!str){
	    this_player()->message("You get "+num+" "+type+" coin"+( (num > 1) ? "s" : "" )+".\n");
	    this_player()->query_environment()->message(this_player()->query_Name()+" gets some money.\n", ({ this_player() }));
	    return 1;
	}
	return str;
    }

    thing = env->present(str) ;
    if(!thing)
	return "No "+str+" to get.\n";

    /* Check to see if the item is willing to be picked up. */
    if (thing->prevent_get()) {
	this_player()->message("You cannot pick that up.\n");
	return 1;
    }
    res = catch(thing->move(this_player()));
    if (res) {
	this_player()->message("You can't pick it up."+res+"\n");
	return 1;
    }
    str = thing->query_short();
    this_player()->message("You get the "+str+".\n");
    this_player()->query_environment()->message(this_player()->query_Name()+" takes "+str+".\n", ({this_player()}));
    return 1;
}

mixed cmd_drop(string str){
    object thing;
    string res, type;
    int num;

    if (!str)
	return "Usage: drop <item>\n";

    /***COINS***/
    if(sscanf(str, "%d %s coin", num, type) == 2 || sscanf(str, "%d %s", num, type) == 2){
	str = catch(this_player()->wealth_move(this_player()->query_environment(), type, num));
	if(!str){
	    this_player()->message("You drop "+num+" "+type+".\n");
	    this_player()->query_environment()->message(this_player()->query_Name()+" drops "+num+" "+type+".\n", ({this_player()}));
	    return 1;
	}
	return str;
    }
    /***END COINS***/
    thing = this_player()->present(str) ;
    if(!thing)
	return "You don't possess "+/*article(str)*/"a"+" "+str+".\n";

    res = catch(thing->move(this_player()->query_environment()));
    if(res){
	this_player()->message("You can't bring yourself to drop it."+res+"\n") ;
	return 1;
    }
    str = thing->query_short();
    this_player()->message("You drop the "+str+".\n") ;
    this_player()->query_environment()->message(this_player()->query_Name()+" drops "+str+".\n", ({this_player()}));
    return 1;
}

mixed cmd_give(string str){
    object thing, target, env;
    string name, item;
    string res;

    if(!str || sscanf(str,"%s to %s",item,name) != 2)
	return "Usage: give <item> to <player>\n";

    thing = this_player()->present(item) ;
    if(!thing)
	return "You don't have a "+item+" to give away.\n";

    env = this_player()->query_environment();
    target = env->present(name);
    if(!target || !target->is_body())
	return "There is no one named "+capitalize(name)+" to give it to.\n";

    res = catch(thing->move(target));

    if(res){
	this_player()->message (capitalize(name)+" cannot carry it.\n");
	return 1 ;
    }
    str = thing->query_short();
    this_player()->message ("You give "+str+" to "+capitalize(name)+".\n");
    name = this_player()->query_Name();
    target->message(name+" gives you "+str+".\n") ;
    this_player()->query_environment()->message (name+" gives "+target->query_Name()+" "+str+".\n",
    ({ target, this_player() }) );
    return 1;
}


/* channeld */
mixed cmd_show (string str){
    if (!str || !strlen(str))
	return "Usage: show <channel>\n";

    this_object()->message(CHANNELD->show(str));
    return 1;
}

mixed cmd_tune (string str){
    if (!strlen (str))
	return "Usage: tune <channel>\n";

    switch(CHANNELD->tune(str)){
    case -1:
	this_object()->message("You tune out of channel " + str + "\n");
	break;
    case 1:
	this_object()->message("You tune into channel " + str + "\n");
	break;
    case 0:
	this_object()->message("You cannot tune into that channel.\n");
    }
    return 1;
}

/* xa - command to show, in brief, another person's injuries */
mixed cmd_xa (string str){
    object target;
    if (!str || !strlen(str)){/* target an attacker */
	target = this_object()->query_target();
	if(!target)return "Not currently in combat!\n";

	this_object()->message(target->query_Name() + ":\n" + target->query_diagram() + "\n");
	return 1;
    }

    target = this_object()->query_environment()->present(str);
    if (target && target->query_has_health()) {
	this_object()->message(target->query_Name() + ":\n" + target->query_diagram() + "\n");
	return 1;
    }
    return "No such thing to xa.\n";
}

/* date - shows the current date/time of the mud's server */
mixed cmd_date (string str){
    return "Date: " + ctime(time()) + "\n";
}


/* alias command - to set and query aliases */
mixed cmd_alias (string str){
	string alias, set, a, b;

	if(!str || !strlen(str)){/* we execute the command to list aliases */
		this_object()->message("Current aliases:" + this_object()->query_user()->query_alias());
		return 1;
	}

	alias = this_object()->query_user()->query_alias(explode(str, " ")[0]);
	if(sscanf(str, "%s %s", a, b) < 2){/* alias query */
		if(alias == str){/* no alias */
			return "No such alias.\n";
		}
		this_object()->message("Alias: " + str + " = " + alias + "\n");
		return 1;
	}

	sscanf(str, "%s %s", str, set);

	/* if we reach here, we're modifying aliases */
	if(!set) return "Usage: alias <name> <value>\n";

	this_object()->message(this_object()->query_user()->add_alias(str, set));
	return 1;
}

/* remove given alias */
mixed cmd_unalias (string str){
	if(!str || !strlen(str)) return "Usage: unalias <alias>\n";

	this_object()->message(this_object()->query_user()->remove_alias(str));
	return 1;
}

/* rudimentary bug reporting */
mixed cmd_bug (string str){
	editor("e /logs/bugs.log");
	return 1;
}