/***************
 * Sea handler *
 ***************/

#include <game/sea_grid.h>

#define SG_ROOM 0
#define SG_FUNC 1

mixed _grid; /**< this will be our ocean */

void create(varargs int clone){
    int i;
    object _ship_, roomy;

    _grid = allocate(X_DIM);
    for(i=X_DIM; i--;){
        _grid[i] = allocate(Y_DIM);
    }
    /* fully allocated */
    /* may add some brief to each room, something seen when observing from the nest */
    _grid[SG_PORT[H_X]][SG_PORT[H_Y]] = ({ clone_object(PORTAGE), "sg_port" }); /* this is the function to handle portage */
    _grid[7][7] = ({ clone_object("/usr/System/obj/portage"), "sg_port" });
    /* need to make portage inheritable so a room knows how to handle docking ships */
    /* need to make the actual ships */
    /* make a ship */


    catch(compile_object(SHIP));
    _ship_ = clone_object(SHIP);

    catch(compile_object(SHIP_ROOM));

    roomy = clone_object(SHIP_ROOM);
    roomy->set_short("Main deck");
    roomy->set_long("The main deck.\n");
    _ship_->set_maindeck(roomy);

    roomy = clone_object(SHIP_ROOM);
    roomy->set_short("Helm");
    roomy->set_long("The helm.\n");
    _ship_->set_helm(roomy);

    roomy = clone_object(SHIP_ROOM);
    roomy->set_short("Fore deck");
    roomy->set_long("The fore deck.\n");
    _ship_->set_foredeck(roomy);

    roomy = clone_object(SHIP_ROOM);
    roomy->set_short("Quarter deck");
    roomy->set_long("The quarter deck.\n");
    _ship_->set_quarterdeck(roomy);

    roomy = clone_object(SHIP_ROOM);
    roomy->set_short("The crowsnest");
    roomy->set_long("The crowsnest.\n");
    _ship_->set_crowsnest(roomy);

    _ship_->set_ship_name("Beagle");
    _ship_->create_ship();
    _ship_->set_plank(_grid[SG_PORT[H_X]][SG_PORT[H_Y]][0]);
}

/* below is where we add attachments to this system */
/** this is called when a ship arrives in the associated square */
void sg_port(object room, object ship){
    /* make a gangplank to board this particular ship */
    ship->ahoy("The ship has arrived at port.\n");
    room->message(ship->query_name()+" arrives at port.\n");
    /*ship->set_plank(room);*/
}

/** this is a default sea square, or nil */
void sg_default(object ship){
    /* can change weather or other such thing */
    ship->ahoy("The winds buffet your sails as the ship moves on.\n");
}

/* manipulants */
/** may need some ship_leave function */
void ship_enter(object ship, int *coords){
    ship->entre(coords);/* for now this is how the ship is self aware,
         later need way for ships to be aware of what ships are in the current vicinity */
    if(_grid[coords[H_X]][coords[H_Y]]){/* something to call */
        call_other(this_object(), _grid[coords[H_X]][coords[H_Y]][SG_FUNC], _grid[coords[H_X]][coords[H_Y]][SG_ROOM],
          ship);
    }else{
        sg_default(ship);
    }
}

atomic void ship_move(object ship, int *heading, int *coords){
    coords[H_X] += heading[H_X];
    if(coords[H_X] < 0 || coords[H_X] >= X_DIM)
        error("Your current heading would run you aground.\n");

    coords[H_Y] += heading[H_Y];
    if(coords[H_Y] < 0 || coords[H_Y] >= Y_DIM)
        error("Your current heading would run you aground.\n");

    if(_grid[coords[H_X]][coords[H_Y]]){/* something to call */
        call_other(this_object(), _grid[coords[H_X]][coords[H_Y]][SG_FUNC], _grid[coords[H_X]][coords[H_Y]][SG_ROOM],
          ship);
    }else{
        sg_default(ship);
    }
    ship->entre(coords);/* for now this is how the ship is self aware */
}

object query_coords(int *coords){
    return _grid[coords[H_X]][coords[H_Y]][SG_ROOM];
}


