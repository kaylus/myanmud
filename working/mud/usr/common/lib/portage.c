/***********
 * portage *
 ***********/
#include <sea_grid.h>

inherit "/usr/common/lib/room";

void set_plank(object ship){
    /*object h;

    h = "/system/users_d"->find_user("hymael");
    if(h)
	    h->catch_tell("Shippy: "+object_name(ship)+" has planked "+short_desc+".\n");
*/
    add_exit(ship->query_name(), ship->query_main());
    message(ship->query_name()+" has lowered its gangplank.\n");
}

void raise_plank(object ship){
    remove_exit(ship->query_name());
    message("The "+ship->query_name()+"'s gangplank is raised.\n");
}
