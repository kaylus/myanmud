/***************
 * Sea handler *
 ***************/

#include <sea_grid.h>

#define SG_ROOM 0
#define SG_FUNC 1

mixed _grid; /* this will be our ocean */

void create(){
	int i;
	object _ship_;

	_grid = allocate(X_DIM);
	for(i=X_DIM; i--;){
		_grid[i] = allocate(Y_DIM);
	}
	/* fully allocated */
	/* may add some brief to each room, something seen when observing from the nest */
	_grid[SG_PORT[H_X]][SG_PORT[H_Y]] = ({ get_object("/world/ocean"), "sg_port" }); /* this is the function to handle portage */
	_grid[7][7] = ({ get_object("/users/hymael/workroom"), "sg_port" });
	/* need to make portage inheritable so a room knows how to handle docking ships */
	/* need to make the actual ships */
	/* make a ship */


	compile_object("/inherit/ship");
	_ship_ = clone_object("/inherit/ship");
	compile_object("/world/ship_main");
	_ship_->set_maindeck("/world/ship_main");
	compile_object("/world/ship_helm");
	_ship_->set_helm("/world/ship_helm");
	compile_object("/world/ship_fore");
	_ship_->set_foredeck("/world/ship_fore");
	compile_object("/world/ship_quar");
	_ship_->set_quarterdeck("/world/ship_quar");
	compile_object("/world/ship_crow");
	_ship_->set_crowsnest("/world/ship_crow");
	_ship_->set_ship_name("Beagle");
	_ship_->create_ship();
	_ship_->set_plank(get_object("/world/ocean"));
}

/* below is where we add attachments to this system */
void sg_port(object room, object ship){/* this is called when a ship arrives in the associated square */
	/* make a gangplank to board this particular ship */
	ship->ahoy("The ship has arrived at port.\n");
	room->room_tell(ship->query_name()+" arrives at port.\n");
	/*ship->set_plank(room);*/
}

void sg_default(object ship){/* this is a default sea square, or nil */
	/* can change weather or other such thing */
	ship->ahoy("The winds buffet your sails as the ship moves on.\n");
}

/* manipulants */
void ship_enter(object ship, int *coords){/* may need some ship_leave function */
	ship->entre(coords);/* for now this is how the ship is self aware,
	     later need way for ships to be aware of what ships are in the current vicinity */
	if(_grid[coords[H_X]][coords[H_Y]]){/* something to call */
		call_other(TO, _grid[coords[H_X]][coords[H_Y]][SG_FUNC], _grid[coords[H_X]][coords[H_Y]][SG_ROOM],
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
		call_other(TO, _grid[coords[H_X]][coords[H_Y]][SG_FUNC], _grid[coords[H_X]][coords[H_Y]][SG_ROOM],
		           ship);
	}else{
		sg_default(ship);
	}
	ship->entre(coords);/* for now this is how the ship is self aware */
}

object query_coords(int *coords){
	return _grid[coords[H_X]][coords[H_Y]][SG_ROOM];
}