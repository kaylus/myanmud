/* player interface commands, may make this an object and directable to a body,
   that way command interfaces can change between players */
#include <weight.h>

#define PREFIX "cmd_"		/* added to the functions */
#define USER this_object()->query_user()	/* temp */
#define BEEP ""
/* all commands will return a fail string or nil, signifying success */

/* return is as follows
	1 - action done, end command search
	nil - continue seek
	string - fail string, continue seek
 */



/* look function */
mixed cmd_look (string str)/* general */
{
    object item;

    if (!str || strlen (str) < 1 || str == "here")
    {				/* we assume they wanted to look at the room */
	this_object ()->message (this_object ()->query_environment ()->query_long ());	/* need to clean this syntax */
	return 1;
    }
    else
    {				/* he wanted to look at str */
	if (strlen (str) > 3 && str[..2] == "at ")
	{			/* strip at */
	    str = str[3..];
	}
	if ((item = this_object ()->present (str)) ||
	(item = this_object ()->query_environment ()->present (str)) != nil)
	{			/* inventory then environ, add in room look at stuff */
	    this_object ()->message (item->query_long () + "\n");
	    return 1;
	}

	if (str == "me")
	{
	    this_object ()->message (this_object ()->query_long () + "\n");
	    return 1;
	}
    }
    return "You cannot see that.\n";
}

mixed cmd_test (string str)
{
    return "new die\n";
}

/* go in a direction */
mixed cmd_go (string str)/* movement */
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

mixed cmd_beep (string str)/* interaction */
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

mixed cmd_kill (string str)/* combat */
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

mixed cmd_inventory (string str)/* general */
{

    object *stuff;
    string name;
    int i, sz, p_cap, p_volume, max_volume, max_cap;

    p_cap = this_object ()->query_p_cap ();
    p_volume = this_object ()->query_p_volume ();
    max_cap = this_object ()->query_capacity ();
    max_volume = this_object ()->query_volume ();

    str = " Carried: [" + p_cap + " / " + max_cap + "] " + WEIGHT_UNIT + "s\n";

    stuff = this_object ()->query_inventory ();
    if (!stuff || !(sz = sizeof (stuff)))
    {
	this_object ()->message (str + "\nYou are empty-handed.\n");
	return 1;
    }
    for (i = 0; i < sz; i++)
    {
	name = stuff[i]->query_short ();
	/* If it has no short it shouldn't show up in your inventory list. */
	if (!name || !strlen (name))
	    continue;

	str += "  " + capitalize (name) + "\n";
    }
    this_object ()->message (str);
    return 1;
}

mixed cmd_wield (string str)/* equipment */
{
    object thing;

    if (!str || !strlen (str))
    {
	return "Usage: wield <item>\n";
    }
    thing = this_object ()->present (str);
    if (thing)
    {

	if ((str = catch (this_object ()->wield (thing))))
	{
	    return str;
	}

	if (catch (call_other (thing, thing->query_wield_func ())))
	{			/* messages not handled */
	    this_object ()->message ("You wield " + thing->query_short () +
	      ".\n");
	    this_object ()->query_environment ()->message (this_object ()->
	      query_Name () +
	      " wields " +
	      thing->
	      query_short () +
	      ".\n", (
	      {
		this_object
		()}
	    ));
	}
	return 1;
    }
    this_object ()->message ("No " + str + " to wield.\n");
    return 1;
}

mixed cmd_unwield (string str)/* equipment */
{
    object thing;


    if (!str || !strlen (str))
    {
	return "Usage: unwield <item>\n";
    }
    thing = this_object ()->present (str);
    if (thing)
    {

	if ((str = catch (this_object ()->unwield (thing))))
	{
	    return str;
	}

	if (catch (call_other (thing, thing->query_unwield_func ())))
	{			/* messages not handled */
	    this_object ()->message ("You unwield " + thing->query_short () +
	      ".\n");
	    this_object ()->query_environment ()->message (this_object ()->
	      query_Name () +
	      " unwields " +
	      thing->
	      query_short () +
	      ".\n", (
	      {
		this_object
		()}
	    ));
	}
	return 1;
    }
    this_object ()->message ("No " + str + " to unwield.\n");
    return 1;
}

mixed cmd_equip (string str)/* equipment */
{
    object thing;

    if (!str || !strlen (str))
    {
	return "Usage: equip <armor>\n";
    }
    thing = this_object ()->present (str);
    if (thing)
    {

	if ((str = catch (this_object ()->equip (thing))))
	{
	    return str;
	}

	if (catch (call_other (thing, thing->query_equip_func ())))
	{			/* messages not handled */
	    this_object ()->message ("You equip " + thing->query_short () +
	      ".\n");
	    this_object ()->query_environment ()->message (this_object ()->
	      query_Name () +
	      " equips " +
	      thing->
	      query_short () +
	      ".\n", (
	      {
		this_object
		()}
	    ));
	}
	return 1;
    }
    this_object ()->message ("No " + str + " to equip.\n");
    return 1;
}

mixed cmd_unequip (string str)/* equipment */
{
    object thing;

    if (!str || !strlen (str))
    {
	return "Usage: unequip <armor>\n";
    }
    thing = this_object ()->present (str);
    if (thing)
    {

	if ((str = catch (this_object ()->unequip (thing))))
	{
	    return str;
	}

	if (catch (call_other (thing, thing->query_unequip_func ())))
	{			/* messages not handled */
	    this_object ()->message ("You unequip " + thing->query_short () +
	      ".\n");
	    this_object ()->query_environment ()->message (this_object ()->
	      query_Name () +
	      " unequips " +
	      thing->
	      query_short () +
	      ".\n", (
	      {
		this_object
		()}
	    ));
	}
	return 1;
    }
    this_object ()->message ("No " + str + " to unequip.\n");
    return 1;
}

mixed cmd_hp (string str)/* combat */
{
    this_object ()->message ("Status:" + this_object ()->query_diagram ());
    return 1;
}

mixed cmd_score (string str)/* combat */
{
    mapping stats;
    int i;
    string *attributes;

    stats = this_object ()->query_stats ();
    attributes = map_indices (stats);
    i = sizeof (attributes);

    str = this_object ()->query_Name () + "\n";
    str += this_object ()->query_diagram ();

    while (i--)
    {
	str +=
	ESC + "[36;1m" + pad (capitalize (attributes[i]) + ": ",
	  15) + ESC + "[0m" + stats[attributes[i]] + "\n";
    }

    this_object ()->message (str);
    return 1;
}

mixed cmd_skills (string str)/* skills */
{
    this_object ()->message (this_object ()->query_skills ());
    return 1;
}

mixed cmd_wealth (string str)
{
    this_object ()->message (this_object ()->query_wealth ());
    return 1;
}

mixed cmd_get (string str)/* add in all kinds of functionality */
{
    object thing;
    string err;

    if (!str || !strlen (str))
    {
	return "Usage: get <item>\n";
    }
    thing = this_object ()->query_environment()->present (str);
    if (thing){/* thing exists in our environment */

	if(thing->prevent_get()){
	    return "You can't get that item.\n";
	}

	if ((err = catch (thing->move(this_object ()))))
	{
	    return err;
	}

	this_object ()->message ("You take " + thing->query_short () + ".\n");
	this_object ()->query_environment ()->message (this_object ()->
	  query_Name () +
	  " takes " +
	  thing->
	  query_short () +
	  ".\n", (
	  {
	    this_object
	    ()}
	));
	return 1;
    }

    this_object ()->message ("No " + str + " to get.\n");
    return 1;
}


mixed cmd_drop (string str){/* add in all kinds of functionality */
    object thing;
    string err;

    if (!str || !strlen (str)){
	return "Usage: drop <item>\n";
    }

    thing = this_object ()->present (str);
    if (thing){/* thing exists in our inventory */

	if(thing->prevent_drop()){
	    return "You can't drop that item.\n";
	}

	if ((err = catch (thing->move(this_object ()->query_environment() )))){
	    return err;
	}

	this_object ()->message ("You drop " + thing->query_short () + ".\n");
	this_object ()->query_environment ()->message (this_object ()->query_Name () +
	  " drops " + thing->query_short() + ".\n", ({ this_object() }) );
	return 1;
    }
    this_object ()->message ("No " + str + " to drop.\n");
    return 1;
}

/* give command in form give item to person */
mixed cmd_give (string str){/* add in all kinds of functionality */
    object thing, person;
    string err, item, target;

    if (!str || !strlen (str) || sscanf(str, "%s to %s", item, target) != 2){
	return "Usage: give <item> to <person>\n";
    }

    thing = this_object ()->present (item);
    if (thing){/* thing exists in our inventory */

	if(thing->prevent_drop()){
	    return "You can't move that item!\n";
	}

	person = this_object()->query_environment()->present(target);
	if(!person || !person->is_body())return "Not a valid recipient.\n";

	if ((err = catch (thing->move(person) ))){
	    return err;
	}

	this_object ()->message ("You give " + thing->query_short () + " to " + person->query_Name() + ".\n");
	person->message(this_object()->query_Name() + " gives you " + thing->query_short() + ".\n");
	this_object ()->query_environment ()->message (this_object ()->query_Name () +
	  " gives " + thing->query_short() + " to " + person->query_Name() + ".\n", ({ this_object(), person }) );
	return 1;
    }
    this_object ()->message ("No " + str + " to give.\n");
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