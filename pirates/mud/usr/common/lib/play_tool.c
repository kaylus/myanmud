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



/* look function, need to add vision checks and such */
mixed
cmd_look (string str)
{
    this_object ()->message (this_object ()->query_environment ()->query_long ());	/* need to clean this syntax */
    return 1;
}

mixed
cmd_test (string str)
{
    if (!strlen (str))
	return "Must put something after test.\n";

    this_object ()->message ("Tested changed.\n");

    return 1;
}

/* go in a direction */
mixed
cmd_go (string str)
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

mixed cmd_inventory(string str){

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
