/**********************************************************
 *                     health.c                           *
 * This will hold the functionality for health it will    *
 * contain the query_has_health, query_health,            *
 * receive_damage, receive_healing, do_tick, and some     *
 * other things which should be encapsulated in this      *
 * function and executed each heartbeat                   *
 *  -Hymael                                               *
 **********************************************************/

private int max_hp, cur_hp;

void init_health(){
    cur_hp=max_hp=250;/* for now */
}

void set_health(int hp){/* mainly for monsters */
    cur_hp=max_hp=hp;
}

/**************************
 * this may be unncessary *
 **************************/
int query_has_health(){
    return 1;
}

/*************************************
 * this returns our current health,  *
 * later to be in abstract form      *
*************************************/
int query_health(){
    return cur_hp;
}

int query_max_health(){
    return max_hp;
}

/*****************************************************************************
* receive sent damage, attack if need be, resist - stuff of that nature     *
* return of 1 denotes damage taken, 0 denotes no damage, 2 denotes resisted *
* some -- May change this over to just return amount of damage done         *
*****************************************************************************/
int receive_damage(int damage, object dealer, varargs string type){
    /* this will eventually mask damage against a body's given resists */
    if(damage < 0 || cur_hp < 0)return 0;
    cur_hp -= damage;
    /* possibly this will be where death occurs */
    if(cur_hp < 0){
	this_object()->die();
    }
    return 1;
}

/****************************
* and its brother function *
****************************/
int receive_healing(int healing){
    if(healing < 0 || cur_hp == max_hp)return 0;
    cur_hp += healing;
    if(cur_hp > max_hp)cur_hp = max_hp;
    return 1;
}

/**************************************************************
* this heals us up, may also add other per heart beat things *
* this will eventually become race specific and such         *
**************************************************************/
void do_tick(){
    receive_healing(2);
    /* do other things, like empty stomachs */
}

string query_xa(){
    switch(cur_hp * 100 / max_hp){/* percentage of */
	/* is ... */
    case 95..100:
	return "[32m[1mperfect condition[0m";
    case 65..94:
	return "[33m[1mstunned[0m";
    case 45..64:
	return "[33mbattered[0m";
    case 25..44:
	return "[31m[1mbloody and bleeding[0m";
    case 10..24:
	return "[31mabout to fall[0m";
    default:
	return "[30m[1malmost dead[0m";
    }
}
