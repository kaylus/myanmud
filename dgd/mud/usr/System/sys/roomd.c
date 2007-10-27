/*
 *  This daemon handles room management and creation
 *  at startup it will load a few rooms and prepare for launch
 *  This should also manage the removal of rooms without a purpose or a pointer to them
 */


object *rooms; /* handles on rooms */
object start_room; /* start room */

object add_room(object room){/* add a room to the register */
	if(!rooms)
		rooms = ({});

	if(!room->is_room())
		error("Object is not a room!");

	rooms += ({ room });
	LOGD->log(object_name(room) + " added to ROOMD.", "roomd");
	return room;
}


void create(varargs int clone){
	rooms = ({});

	/* load our room object */
	if(!find_object(ROOM)) compile_object(ROOM);

	/* create a start room */
	start_room = clone_object(ROOM);
	start_room->set_short("Start room");
	start_room->set_long("This is the ubiquitous start room.\n");
}

object query_start_room(){/* return the default room */
	return start_room;
}

