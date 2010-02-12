/*************************
 *       armor.c         *
 *************************/
#include <config.h>

inherit OBJECT;

static string type;              /* what slot is this armor? */
static int ac;                   /* armor's inherent armor class */
static string equip_func;        /* function called when armor is equipped */
static string unequip_func;      /* function called when armor is unequipped */
static string hit_func;          /* possibly called when player is hit */


/****************
 * sets/queries *
 ****************/
int is_armor() { return 1; }

void set_type(string str){ type = str; }

string query_type(){ return type; }

void set_ac(int val){ ac = val; } /* can be negative for cursed armors */

int query_ac(){ return ac; }

void set_equip_func(string fun)   { equip_func = fun;    }
void set_unequip_func(string fun) { unequip_func = fun;  }

string query_equip_func()         { return equip_func;   }
string query_unequip_func()       { return unequip_func; }

void set_hit_func(string fun) { hit_func = fun; }

string query_hit_func() { return hit_func; }

void set_id (string *newid) {/* assures we always have id armor */
    ::set_id (newid +({ "armor" }));
}