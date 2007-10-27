/*
   container.c
   This file is to be inherited by any object that is capable of
   holding other objects. It handles inventory_related business,
   which is defined here rather than in the auto object.
   Do not confuse this container with a bag. Bags need to inherit this,
   but player.c and room.c (which also contain objects) also inherit
   this. There is no support for opening, closing, or locking these
   containers, since many containers do not desire these options.
   You may wish to write an inheritable bag.c if you plan on having
   many bags (or chests or other such) in your MUD.
   Begun by Mobydick, 5-25-94
   Hymael - may push get/put to different inheritable
*/

inherit OBJECT;

private static object *inventory;

/***PROTOS***/
object present(string id);

static void create(int clone){
    /* Hymael - adding in bag functionality */
#if 0
    add_command("get",  "get_from");
    add_command("put",  "put_in");/* look in container must be utilized */
    add_command("look", "look_in");
#endif

}

int is_container(){ return 1; }

/************************************
 * Hymael - coded in weight check   *
 * and atomic                       *
 * slide is sans weight calc        *
 ************************************/
atomic void receive_object(object ob, varargs int slide){
    if(!inventory)
	inventory = ({});

	if(ob->prevent_get())
		error("This object cannot be in inventory.");

    inventory += ({ ob });
    if(!slide)
	::receive_object(ob); /* this is the weight check */
}

atomic void release_object(object ob, varargs int slide){
    if(!inventory || !sizeof(({ ob }) & inventory))
	error("Not in container.\n");

    inventory -= ({ ob });
    if(!slide)
	::release_object(ob);
}

#if 0
int look_in(string str){
    string bag;
    int i;

    if(!str || !sscanf(str, "in %s", bag) || !id(bag))
	return 0;

    /* let's look inside */
    catch(i = sizeof(inventory));
    say(TPN+" looks inside "+article(bag)+" "+bag+".\n");
    if(!i){
	write("Nothing inside of that.\n");
	return 1;
    }
    str = "Contents:\n";
    while(i--){
	str += "  "+inventory[i]->query_short()+"\n";
    }
    write(str);
    return 1;
}
#endif

/* sneaky but what the fuck */
atomic void _get(object item, object getter){
    if(environment != getter){/* normal movement */
	item->move(getter);
	return;
    }
    getter->receive_object(item, 1);
    release_object(item);
    item->slide(getter);
}
#if 0
int get_from(string str){/* handle form get X from Y */
    string item, bag, type;
    object ob;
    int number;

    if(!str || sscanf(str, "%s from %s", item, bag) != 2 || !id(bag))/* not this bag */
	return 0;

    /***MONEY***/
    if(sscanf(item, "%d %s coin", number, type) == 2 || sscanf(item, "%d %s", number, type) == 2){
	string err;
	ob = present(type);
	if(!ob || !ob->is_coins())
	    return fail_msg("You don't see that money.\n");

	err = catch(ob->coin_move(TP, number, (environment == TP)));
	if(err){
	    return fail_msg(err);
	}
	write("You get "+number+" "+type+" from "+bag+".\n");
	say(TPN+" gets some money from "+bag+".\n");
	return 1;
    }
    /***END MONEY***/

    if(item == "all"){
	int i;
	catch(i = sizeof(inventory));
	if(!i)
	    return fail_msg("Nothing in "+bag+".\n");

	while(i--){/* proceed to empty */
	    item = catch(_get(inventory[i], TP));
	}
	write("You remove everything from the "+bag+".\n");
	say(TPN+" gets everything from "+article(bag)+" "+bag+".\n");
	return 1;
    }
    ob = present(item);
    if(!ob)
	return fail_msg("No "+item+" in "+bag+".\n");

    /* ob exists in this bag */
    if((str = catch(_get(ob, TP)))){/* no move */
	write(str);
    } else { /* moved */
	str = ob->query_short();
	write("You take the "+str+" from "+bag+".\n");
	say(TPN+" gets a "+str+" from "+article(bag)+" "+bag+".\n");
    }
    return 1;
}

/* sneaky but what the fuck */
atomic void _put(object item, object putter){
    if(environment != putter){/* normal movement */
	item->move(TO);
	return;
    }
    receive_object(item);
    putter->release_object(item, 1);
    item->slide(TO);
}



int put_in(string str){/* handle form put X in(to) Y */
    string item, bag, type;
    object ob;
    int number;

    if(!str || sscanf(str, "%s in %s", item, bag)!=2 || !id(bag))/* not this bag */
	return fail_msg("Usage: put <item> in <bag>\n");

    /***MONEY***/
    if(sscanf(item, "%d %s coin", number, type) == 2 || sscanf(item, "%d %s", number, type) == 2){
	string err;

	err = catch(TP->wealth_move(TO, type, number, (environment == TP)));
	if(err){
	    return fail_msg(err);
	}
	write("You put "+number+" "+type+" into "+bag+".\n");
	say(TPN+" puts some money into "+bag+".\n");
	return 1;
    }
    /***END MONEY***/

    ob = TP->present(item);
    if(!ob)
	return fail_msg("You don't possess "+article(item)+" "+item+".\n");

    if(ob == TO)
	return fail_msg("You cannot put an object inside itself.\n");

    /* ob exists in this bag */
    if((str = catch(_put(ob, TP)))){/* move fail */
	write(str);
    } else { /* moved */
	str = ob->query_short();
	write("You put "+str+" into "+bag+".\n");
	say(TPN+" puts a "+str+" into "+article(bag)+" "+bag+".\n");
    }
    return 1;
}
#endif
/* query_inventory() returns the inventory of this object. Right now
   I'm passing the array which is the Wrong Thing. I need to alter
   this to return a copy. */

object *query_inventory() {
    if(!inventory)
	inventory = ({});

    inventory -= ({ nil });
    return inventory[..];
}

/* The present function takes a string and returns the first object in
   the inventory of the object which takes that string as id.
   If the string passed is "me", then the body of this_user() will be
   returned if in the container. If the string is "here", then the
   container will be returned. There are no other magic words.
   Does not, as yet, grok the concept of "sword 2".
   It is more object-oriented to have this in container, where it can
   be overriden by a given container if that is desired, than to have
   it as a kfun which was the old LPC way.
*/

object present(string id){
    int sz, num;
    string hardid;

    if(!inventory || (sz = sizeof(inventory)) == 0)
	return nil;
#if 0
    if(id == "me"){
	if(member_array(TP, inventory) > -1){
	    return TP;
	}
	return nil;
    }
#endif
    if(id && sscanf(id, "%s %d", hardid, num) == 2){/* we have sword 2 form */
	if(num > 0){
	    while(sz--){
		if(inventory[sz]->id(hardid) && --num == 0)
		    return inventory[sz];
	    }
	}
	return nil;
    }
    /* I'm not sure this is really correct, but it makes "look at here" work. */
    if (id == "here")
	return this_object();

    while(sz--){
	if(inventory[sz]->id(id))
	    return inventory[sz];
    }
    return nil;
}

int object_present (object ob) {
    if (!inventory || !sizeof(inventory))
	return 0;

    return (member_array(ob,inventory) != -1);
}

