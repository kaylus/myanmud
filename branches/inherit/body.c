/*******************************************************
 *                   body.c                            *
 * This will hold the functionality of equipping items *
 * in specific slots                                   *
 * and other bodily functions                          *
 * -Hymael                                             *
 *******************************************************/
#include <config.h>
#include <body.h>

inherit container CONTAINER;
inherit STATS; /* temp */
inherit HEALTH;
inherit combat COMBAT;
inherit WEAPON;
inherit SKILLS;

/**************************************
 * mapping of worn items - to be made *
 * non static at some point           *
 **************************************/
static mapping armors;  	/* does not include shield */

/*************************************
 * wielded[BP_ARMS[0]]=weapon object *
 *************************************/
static mapping wielded; 	/* includes shield */
static mapping armor_class; /* individual body parts' ac */
static mapping hit_spread;  /* contains mapping of hit percentages */
static string *arms;        /* valid arms */

static int     _state;      /* retains state of body */

void create(){ /* allocates for speed */
	if(!armors)
		armors      = ([]);/*allocate(sizeof(BP_ALL));*/

	if(!armor_class)
		armor_class = ([]);/*allocate(map_sizeof(BP_ALL));*/

	if(!wielded)
		wielded     = ([]);/*allocate(map_sizeof(BP_ARMS));*/

	/***WEIGHT STUFF***/
	set_bulk(200);
	set_weight(200);
	set_capacity(150);
	set_volume(150);

	hit_spread = BODY_PARTS;
	arms       = BP_ARMS;
	_state     = S_FREE; /* we're free of all states */
	combat::create();
}

void set_arms(string *value){
	arms = value;
}

int query_arms(){ return sizeof(arms); }

void refresh_health(){
	arms = BP_ARMS;
	_state = S_FREE;
	hit_spread = BODY_PARTS;
	::refresh_health();
}

int is_body(){ return 1; }

void incr_ac(string part, int val){
	armor_class[part] += val;
}

void decr_ac(string part, int val){
	armor_class[part] -= val;
}

int total_valies(int *vals, int sz){
	int total;
	while(sz--){/* would like to make this only calculate once, at change */
		total += vals[sz];
	}
	return total;
}

string target(){/* target a random body part */
	string *indies;
	int *valies, total, i, cur, rand;
	indies = map_indices(hit_spread);
	valies = map_values(hit_spread);
	i = sizeof(valies);
	rand = random(total_valies(valies, i));
	while(i--){
		cur += valies[i];
		if(rand < cur){/* we've found our target */
			return indies[i];
		}
	}
	/* shouldn't reach this point, might default to torso since that'll always be there */
	error("No body target found!");
	return nil;
}

int ac_of(string body_part){/* this retrieves the ac of a given part */
	return armor_class[body_part];
}

int set_state(int val){/* events need to be added to a global header */
	switch(val){
	case S_PRONE:/* set state to prone, subject on ground */
		if(_state & S_PRONE){/* already prone */
			return 0;
		}
		_state &= ~S_COVER; /* lose cover */
		_state &= ~S_MOUNT; /* lose mount */
		_state &= ~S_FLY;   /* stop flying? */
		_state |= S_PRONE;  /* go prone */
		this_object()->event("prone");/* we issue an event that we've fallen */
		return 1;
	case S_LOCK:/* set state to locked, in close quarters combat */
		if(_state & S_LOCK){/* already locked */
			return 0;
		}
		_state &= ~S_COVER; /* lose cover */
		_state &= ~S_GRAP;  /* ungrapple */
		_state |= S_LOCK;   /* locked in combat */
		this_object()->event("lock");
		return 1;
	case S_MOUNT:/* mount up */
		if(_state & (S_LOCK | S_GRAP | S_PRONE)){/* can't mount */
			return 0;
		}
		_state &= ~S_COVER; /* lose cover */
		_state |= S_MOUNT;  /* mounted */
		this_object()->event("mount");
		return 1;
	case S_GRAP:/* grappling state */

		_state &= ~S_COVER;
		/*_state &= ~S_MOUNT;*/
		_state &= ~S_FLY;
		_state |= S_GRAP;
		return 1;
	case S_FLY: /* go airborn */
		if(_state & (S_LOCK | S_PRONE | S_GRAP)){/* no no */
			return 0;
		}
		_state |= S_FLY;
		return 1;
	}
	error("Faulty state!");
	return nil;
}

int query_state(){ return _state; }

/*************************
 * weaponry and shields  *
 * nil return is success *
 *************************/
string wield(object obj){
	int sz, i;

	if(!obj->is_weapon() && obj->query_type() != "shield"){
		return "You cannot wield that.\n";
	}

	if(obj->is_broke()){
		return "That weapon is broken.\n";
	}

	if(!(sz = sizeof(arms))){
		return "You haven't any arms, see a doctor.\n";
	}

	if(obj->query_two_handed()){
		sz -= 1;/* so we chug along to one before max */
		for(i=0; i<sz; i++){
			if(!wielded[arms[i]] && !wielded[arms[i+1]]){/* wield */
				wielded[arms[i]]   = obj;
				wielded[arms[i+1]] = 1; /* place holder */
				vector_weapons();
				return nil;
			}
		}
		return "You haven't the arms to wield that.\n";
	}

	if(!obj->query_is_offhand() && obj->query_type() != "shield"){
		if(!wielded[arms[0]]){
			wielded[arms[0]] = obj;
			vector_weapons();
			return nil;
		}

		if(wielded[arms[0]]->query_is_offhand() ||
		   wielded[arms[0]]->query_type() == "shield"){/* push down line and wield */
			while(sz-- > 0){
				if(!wielded[arms[sz]]){
					wielded[arms[sz]] = wielded[arms[0]];
					wielded[arms[0]] = obj;
					vector_weapons();
					return nil;
				}
			}
		}

		return "You haven't the hands to wield that.\n";
	}

	for(i=0; i<sz; i++){
		if(!wielded[arms[i]]){
			wielded[arms[i]] = obj;
			vector_weapons();
			return nil;
		}
	}

	return "You haven't the hands to wield that.\n";
}

/**********
 * remove *
 **********/
string unwield(object obj){
	object *values;
	string *indices;
	int i, sz, x;

	values = map_values(wielded);
	if((i = member_array(obj, values)) > -1){
		indices = map_indices(wielded);
		cease_weapon(wielded[indices[i]]);
		wielded[indices[i]] = nil;
		if(obj->query_two_handed()){
			x = member_array(indices[i], arms);
			wielded[arms[(x+1)]] = nil; /*problem arises in arrays sorted differently */
		}

		if(!wielded[arms[0]]){/* check for shifting */
			sz = sizeof(arms);
			for(i=1; i<sz; i++){
				if(wielded[arms[i]] && wielded[arms[i]] != 1){
					wielded[arms[0]] = wielded[arms[i]];
					wielded[arms[i]] = nil;
					return nil;
				}
			}
		}
		return nil;
	}
	return "You're not wielding that.\n";
}

/****************
 * and a query  *
 ****************/
int query_wielded(object obj){
	object *values;

	values = map_values(wielded);
	return (values && member_array(obj, values) > -1);
}

object query_primary(){
	return (arms && arms[0]) ? wielded[arms[0]] : nil;
}

object *query_weapons(){
	mixed *values;
	int i;
	values = map_values(wielded);
	i = sizeof(values);
	while(i--){
		if(values[i] == 1 || !values[i]->is_weapon()){
			values[i] = nil;
		}
	}
	values -= ({ nil });
	return values;
}

/********************************************
 * outside we call this to push onto armors *
 * values : nil is success, otherwise fmess *
 ********************************************/
string equip_armor(object obj){
	string type, slot;

	type = obj->query_type();
	slot = obj->query_slot();
	if(!type || !slot){
		return "Faulty armor specs, inform a wiz.\n";
	}
	if(obj->is_broke()){
		return "That armor is broken and needs the care of a craftsman.\n";
	}
	if(type == "shield"){/* deal with shield */
		return wield(obj);
	}
	if(!query_heft(slot)){
		return "You seem to be missing your "+slot+".\n";
	}
	if(armors[slot] && armors[slot]->query_type() == type){
		return "You're already wearing something of that nature.\n";
	}
	/* we should be good to equip, should I put messages in here? */
	armors[slot] = obj;
	incr_ac(slot, obj->query_ac());
	return nil;
}

/***********************
 * remove, nil success *
 ***********************/
string unequip_armor(object obj){
	object *values;
	string *indices;
	int i;
	if(obj->query_type() == "shield"){
		return unwield(obj);
	}
	values = map_values(armors);
	if((i = member_array(obj, values)) > -1){
		indices = map_indices(armors);
		armors[indices[i]] = nil;
		decr_ac(indices[i], obj->query_ac());
		return nil;
	}
	return "You aren't wearing the "+obj->query_short()+".\n";
}

/****************
 * and a query  *
 ****************/
int query_equipped(object obj){
	object *values;

	if(obj->query_type() == "shield"){
		return query_wielded(obj);
	}
	values = map_values(armors);
	return (values && member_array(obj, values) > -1);
}

/**********************
 * disable a limb     *
 **********************/
object *disable_limb(string limb){
	int i;
	object *items; /* for later expansion */

	items = ({});
	/* remove from hitspread */
	if(hit_spread[limb]){
		hit_spread[limb] = nil;
	}
	if((i = member_array(limb, arms)) > -1){
		if(wielded[limb]){
			if(wielded[limb] == 1){/* deal with two-hander */
				unwield(wielded[arms[i-1]]);
			}else{
				items += ({ wielded[limb] });
				unwield(wielded[limb]);
			}
		}
		arms -= ({ limb });
	}

	if(armors[limb]){
		items += ({ armors[limb] });
		unequip_armor(armors[limb]);
		return items;
	}
	return items;
}

int intercept(object attacker, object weapon){/* designed to be overriden */
	int i;
	string func;

	i = sizeof(arms);
	while(--i >= 0){
		if(wielded[arms[i]] && wielded[arms[i]] != 1){
			if((func = wielded[arms[i]]->query_intercept_func())){/* items defines an intercept */
				return call_other(wielded[arms[i]], func, this_object(), attacker, weapon);
			}

		   	if(wielded[arms[i]]->query_type() == "shield" /* || wielded[arms[i]]->can_parry()*/){
				if(random(100) < 10){/* successful intercept */
					string sname, aname;
					sname = this_object()->query_cap_name();
					aname = attacker->query_cap_name();
					attacker->catch_tell("Your weapon clangs against "+sname+"'s shield.\n");
					this_object()->catch_tell(aname+"'s weapon clangs against your shield.\n");
					attacker->query_environment()->room_tell(sname+"'s shield intercepts "+
															 aname+"'s attack.\n",
															 ({ this_object(), attacker }) );
					if(random(3)){/* a third the chance to break */
						wielded[arms[i]]->handle_break(attacker, weapon, this_object());
						weapon->handle_break(attacker, wielded[arms[i]]);
					}
					return 1;
				}
			}
		}
	}
	return 0;
}

void set_id(string *newid){/* assures we don't have id weapon */
    container::set_id (newid);
}

int handle_break(object owner, varargs object armor, int damage){
	return 0; /* so we don't break */
}
#if 0

int query_ac(){
	return ac + this_object()->query_stat("dexterity");
}/* add in attribute checks */

object query_primary(){
	if(!wielded) wielded=([]);
	return wielded[WIELDS[0]];
}

object query_secondary(){
	if(!wielded) wielded=([]);
	return wielded[WIELDS[1]];
}

#endif
/****************************
 * overloads for container  *
 * these now check for worn *
 * and wielded items        *
 ****************************/
atomic void release_object(object ob, varargs int slide){
   	/* check equipped, if so, unequip it */
   	int func, fun;
   	::release_object(ob, slide);  /* pass the ball */
   	if(query_equipped(ob) ||
   	   (ob->query_type() == "shield" &&
   	   query_wielded(ob))){/* don't like doing messages here, but fuck it */
   		unequip_armor(ob);
   		catch(fun = call_other(ob, ob->query_unequip_func()));
		if(!fun){/* messages not handled */
			TO->catch_tell("You unequip "+ob->query_short()+".\n");
   			TO->query_environment()->room_tell(
				TO->query_cap_name()+" unequips "+ob->query_short()+".\n",
				({ TO }) );
		}
   	}else if(query_wielded(ob)){
		unwield(ob);
		catch(fun = call_other(ob, ob->query_unwield_func()));
		if(!fun){/* messages not handled */
			this_object()->catch_tell("You unwield "+ob->query_weapon_name()+".\n");
			this_object()->query_environment()->room_tell(
				this_object()->query_cap_name()+" unwields "+ob->query_weapon_name()+".\n",
				({ this_object() }) );
		}
	}
}

/*************************
 * check the sexay boday *
 *************************/
string query_long() {
    string ret, describe, *indices, *windices;
    int i, total, sz;
    object *inventory, *worn_items, *wielded_items;

    inventory = TO->query_inventory() ;
    ret = "";
    total = 0;
    if (wielded){
		wielded_items = map_values(wielded);
		windices = map_indices(wielded);
		for(i=0,sz=sizeof(windices); i<sz; i++){
			if(!wielded[windices[i]] || wielded[windices[i]]==1)
				continue;
			ret += "\n"+pad(capitalize(windices[i])+": ",15)+
				wielded[windices[i]]->query_short();
			total++;
		}
	}
    if (armors){
		worn_items = map_values(armors);
		indices = map_indices(armors);
		for(i=0,sz=sizeof(indices); i<sz; i++){
			ret += "\n"+pad("Worn on "+indices[i]+" as "+armors[indices[i]]->query_type()+": ",30)+
			       armors[indices[i]]->query_short();
		}
		total += sz;
	}
	ret += "\n";
    if (!inventory || ((sz=sizeof(inventory))-total)==0) {
        ret += capitalize(TO->query_subjective())+" is not carrying anything.\n";
    } else {
        ret += capitalize(TO->query_subjective())+" is carrying:\n";
	for (i=0; i<sz; i++){
	    if(worn_items && member_array(inventory[i], worn_items) > -1)continue;
	    if(wielded_items && member_array(inventory[i], wielded_items)>-1)continue;
	    ret += "  "+inventory[i]->query_short()+"\n";
        }
    }
    return ret;
}