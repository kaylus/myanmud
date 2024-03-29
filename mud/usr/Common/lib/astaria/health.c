/**
 *                     health.c                           
 * This will hold the functionality for health it will    
 * contain the query_has_health, query_health,            
 * receive_damage, receive_healing, do_tick, and some     
 * other things which should be encapsulated in this      
 * function and executed each heartbeat                   
 *  @author Hymael                                               
 */
# include <game/body.h>

private int max_hp, cur_hp;

void init_health(){
    cur_hp = max_hp = 250;/* for now */
}

void set_health(int hp){/* mainly for monsters */
    cur_hp = max_hp = hp;
}

/**
 * this may be unncessary 
 */
int query_has_health(){
    return 1;
}

/**
 * this returns our current health,  
 * later to be in abstract form      
 */
int query_health(){
    return cur_hp;
}

int query_max_health(){
    return max_hp;
}

/**
 * receive sent damage, attack if need be, resist - stuff of that nature     
 * @retval return of 1 denotes damage taken, 0 denotes no damage, 2 denotes resisted some
 * @todo May change this over to just return amount of damage done         
 */
int receive_damage(int damage, object dealer, varargs string type){
    /* this will eventually mask damage against a body's given resists */
    if(damage < 0 || cur_hp < 0)return 0;
    cur_hp -= damage;
    /* possibly this will be where death occurs */
    if(cur_hp < 0){
	call_out("die", 0);
    }
    return 1;
}

/**
 * and its brother function 
 */
int receive_healing(int healing){
    if(healing < 0 || cur_hp == max_hp)return 0;
    cur_hp += healing;
    if(cur_hp > max_hp)cur_hp = max_hp;
    return 1;
}

/**
 * this heals us up, may also add other per heart beat things 
 * this will eventually become race specific and such         
 */
void do_tick(){
    receive_healing(2);
    /** @todo do other things, like empty stomachs */
}

string query_xa(){
    switch(cur_hp * 100 / max_hp){/* percentage of */
	/* is ... */
    case 95..100:
	return "%^BOLD%^%^GREEN%^perfect condition%^RESET%^";
    case 65..94:
	return "%^BOLD%^%^YELLOW%^stunned%^RESET%^";
    case 45..64:
	return "%^YELLOW%^battered%^RESET%^";
    case 25..44:
	return "%^BOLD%^%^RED%^bloody and bleeding%^RESET%^";
    case 10..24:
	return "%^RED%^about to fall%^RESET%^";
    default:
	return "%^BOLD%^%^BLACK%^almost dead%^RESET%^";
    }
}

void refresh_health(){
  cur_hp = max_hp;
}

/** wrapper for dropping corpse, @todo error checking */
static void _die(){
	int i, sz;
	object *inv, corpse;
	
	if(!find_object(CORPSE))compile_object(CORPSE);
	
	corpse = clone_object(CORPSE); 
	catch{
	inv = this_object()->query_inventory();
	
	for(i=sizeof(inv) ; --i >= 0; ){	
			inv->move(corpse); /* move items onto corpse */
	}
	}
	
	corpse->move(this_object()->query_environment());
	corpse->set_name(this_object()->query_name());
}

void die(){
	event("death", this_object());
	/* drop corpse and all that good stuff */
	_die();
	
	this_object()->pacify();
	this_object()->message("%^BOLD%^%^BLACK%^You have died.%^RESET%^\n");
	this_object()->query_environment()->message(this_object()->query_Name()+" has died.\n", ({this_object()}));
	
	this_object()->move(ROOMD->query_labyrinth(), "", 1, 1);
	refresh_health();
	/** @todo print death message to them */
	
	LOGD->log(this_object()->query_Name()+" died", "combat");

}