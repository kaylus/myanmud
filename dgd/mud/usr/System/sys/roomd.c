/*
 *  This daemon handles room management and creation
 *  at startup it will load a few rooms and prepare for launch
 *  This should also manage the removal of rooms without a purpose or a pointer to them
 */


object *rooms; /* handles on rooms */

void create(varargs int clone){
	rooms = ({});

	/* load our room object */
	if(!find_object(ROOM)) compile_object(ROOM);

	/* create a start room */
	rooms += clone_object(ROOM);
	rooms[0]->set_short("Start room");
	rooms[0]->set_long("This is the ubiquitous start room.\n");
}

object query_start_room(){/* return the default room */
	return rooms[0];
}

