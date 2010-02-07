/*******************************************************
 *                   body.c                            *
 * This will hold the functionality of equipping items *
 * in specific slots                                   *
 * and other bodily functions                          *
 * -Hymael                                             *
 *******************************************************/
#include <config.h>
#define WIELDS ({ "primary", "secondary" })
#define ARMORS ({ "suit", "gauntlets", "gloves", "greaves", "ring", "helm",\
"cloak", "shoulder", "waist", "feet", "shield" })

inherit container CONTAINER;
inherit WEAPON;
inherit COMBAT;
inherit HEALTH;
inherit "/inherit/stats.c"; /* temp */

/**************************************
 * mapping of worn items - to be made *
 * non static at some point           *
 **************************************/
private static mapping worn;

/************************************
 * wielded["primary"]=weapon object *
 ************************************/
static mapping wielded;

static int ac;               	/* this will be our body's armor class */

void create(){ /* empty */ }

int query_ac(){
	return ac + this_object()->query_stat("dexterity");
}/* add in attribute checks */

void set_id(string *newid){/* assures we always have id weapon */
    container::set_id (newid);
}

int is_body(){ return 1; }

void incr_ac(int val){ ac += val; }
void decr_ac(int val){ ac -= val; }

object query_primary(){
	if(!wielded) wielded=([]);
	return wielded[WIELDS[0]];
}

object query_secondary(){
	if(!wielded) wielded=([]);
	return wielded[WIELDS[1]];
}

/******************************************
 * outside we call this to push onto worn *
 * values : 0 fail, 1 success             *
 ******************************************/
int set_worn(object obj){/* calculate armor total ac */
	string type;
	if(!wielded) wielded=([]);
	if(!worn)    worn   =([]);
	type = obj->query_type();
	if(type && !worn[type]){
		if(type == "shield" && wielded[WIELDS[1]]){
			return 0; /* can't equip shield over weapon */
		}
		worn[type]=obj;
		incr_ac(obj->query_ac());
		return 1;
	}
	return 0;
}

/****************
 * and a query  *
 ****************/
int query_worn(object obj){/* remove ac */
	object *values;
	if(!wielded) wielded = ([ ]);
	if(!worn)    worn   = ([ ]);

	values = map_values(worn);
	if(values && member_array(obj, values)>-1){
		return 1;
	}
	return 0;
}

/**********
 * remove *
 **********/
int remove_worn(object obj){
	object *values;
	string *indices;
	int i;
	if(query_worn(obj)){
		values = map_values(worn);
		indices = map_indices(worn);
		i = member_array(obj, values);
		worn[indices[i]] = nil;
		decr_ac(obj->query_ac());
		return 1;
	}
	return 0;
}

/*******************************
 * query listing of worn items *
 *******************************/
mapping query_worn_listing(){
	return copy(worn);
}


/*************************
 * wield some shit       *
 *  1- success           *
 *  0- fail by no slot   *
 * -1- fail by twohander *
 * -2- fail by shield    *
 *************************/
int wield( object obj ){
	if(!wielded) wielded=([]);
	if(!worn)    worn   =([]);
	if(!obj->is_weapon()) return 0;

	if(obj->query_two_handed()){
		if(!wielded[WIELDS[0]] && !wielded[WIELDS[1]] &&
			!worn["shield"]){/* wield this beastly two hander */
			wielded[WIELDS[0]] = obj;
			wielded[WIELDS[1]] = 1; /* placeholder, note when unwielding 2hander */
			return 1;
		}else{
			return -1;
		}
	}else if(!obj->query_is_offhand()){
		if(!wielded[WIELDS[0]]){
			wielded[WIELDS[0]] = obj;
			return 1;
		}else if(wielded[WIELDS[0]]->query_is_offhand() && !worn["shield"] &&
			!wielded[WIELDS[1]]){/* push to second and wield */
			wielded[WIELDS[1]] = wielded[WIELDS[0]];
			wielded[WIELDS[0]] = obj;
			return 1;
		}else{
			return 0;
		}
	}else{
		if(!wielded[WIELDS[0]]){
			wielded[WIELDS[0]] = obj;
			return 1;
		}else if(!wielded[WIELDS[1]]){
			if(!worn["shield"]){
				wielded[WIELDS[1]] = obj;
				return 1;
			}else{
				return -2;
			}
		}
	}
	return 0;
}

/****************
 * and a query  *
 ****************/
int query_wielded(object obj){
	object *values;
	if(!wielded) wielded=([]);
	if(!worn)    worn   =([]);

	values = map_values(wielded);
	if(values && member_array(obj, values)>-1){
		return 1;
	}
	return 0;
}

/**********
 * remove *
 **********/
int unwield(object obj){
	object *values;
	string *indices;
	int i;
	if(!wielded) wielded=([]);
	if(!worn)    worn   =([]);

	if(query_wielded(obj)){
		values = map_values(wielded);
		indices = map_indices(wielded);
		i = member_array(obj, values);
		wielded[indices[i]]=nil;
		if(obj->query_two_handed()){
			wielded[WIELDS[1]]=nil;
		}else if(wielded[WIELDS[1]] && !wielded[WIELDS[0]]){/* move secondary to primary */
			wielded[WIELDS[0]] = wielded[WIELDS[1]];
			wielded[WIELDS[1]] = nil;
		}
		return 1;
	}
	return 0;
}

/****************************
 * overloads for container  *
 * these now check for worn *
 * and wielded items        *
 ****************************/
int release_object (object ob) {
   	/* check equipped, if so, unequip it */
   	int res, func, fun;
   	res = ::release_object(ob);/* pass the ball */
   	if(res && query_worn(ob)){/* don't like doing messages here, but fuck it */
   		remove_worn(ob);
   		catch(fun = call_other(ob, ob->query_unequip_func()));
		if(!fun){/* messages not handled */
			this_object()->catch_tell("You unequip "+ob->query_short()+".\n");
   			this_object()->query_environment()->room_tell(
				this_object()->query_cap_name()+" unequips "+ob->query_short()+".\n",
				({ this_object() }) );
		}
   	}else if(res && query_wielded(ob)){
		unwield(ob);
		catch(fun = call_other(ob, ob->query_unwield_func()));
		if(!fun){/* messages not handled */
			this_object()->catch_tell("You unwield "+ob->query_weapon_name()+".\n");
			this_object()->query_environment()->room_tell(
				this_object()->query_cap_name()+" unwields "+ob->query_weapon_name()+".\n",
				({ this_object() }) );
		}
	}
   	return res; /* propogate through */
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
		for(i=0,sz=sizeof(windices);i<sz;i++){
			if(!wielded[windices[i]] || wielded[windices[i]]==1)
				continue;
			ret += "\n"+pad(capitalize(windices[i])+": ",15)+
				wielded[windices[i]]->query_short();
			total++;
		}
	}
    if (worn){
		worn_items = map_values(worn);
		indices = map_indices(worn);
		for(i=0,sz=sizeof(indices);i<sz;i++){
			ret += "\n"+pad(capitalize(indices[i])+": ",15)+worn[indices[i]]->query_short();
		}
		total += sz;
	}
	ret += "\n";
    if (!inventory || ((sz=sizeof(inventory))-total)==0) {
        ret += capitalize(TO->query_subjective())+" is not carrying anything.\n" ;
    } else {
        ret += capitalize(TO->query_subjective())+" is carrying:\n" ;
	for (i=0;i<sz;i++) {
	    if(worn_items && member_array(inventory[i], worn_items)>-1)continue;
	    if(wielded_items && member_array(inventory[i], wielded_items)>-1)continue;
	    ret += "  "+inventory[i]->query_short()+"\n" ;
        }
    }
    return ret ;
}