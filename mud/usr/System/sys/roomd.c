/*
 *  This daemon handles room management and creation
 *  at startup it will load a few rooms and prepare for launch
 *  This should also manage the removal of rooms without a purpose or a pointer to them
 */
#define DIRS ([ "east" : "west", "south" : "north", "west" : "east", "north" : "south", "up" : "down", "down" : "up", "northwest" : "southeast", "southeast" : "northwest", "northeast" : "southwest", "southwest" : "northeast" ])
#define A_DIRS ({ "east", "west", "south", "north", "up", "down", "northwest", "northeast", "southwest", "southeast" })

object *rooms; /* handles on rooms */
object start_room; /* start room */
object meat_locker; /* meat locker */
object labyrinth; /* where people go when they die */

void connect_rooms(object room1, object room2, string via1, varargs string via2, int oneway);

/* To flip a direction. */

string flip_dir(string dir){
    if(member_array(dir, A_DIRS) > -1){
	return DIRS[dir];
    }
    return dir;
}

object add_room(object room){/* add a room to the register */
    if(!rooms)
	rooms = ({});

    if(!room->is_room())
	error("Object is not a room!");

    rooms += ({ room });
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

    meat_locker = clone_object(ROOM);
    meat_locker->set_short("This is the meat locker");
    meat_locker->set_long("This is where inactive bodies go to play.\n");

    labyrinth = clone_object(ROOM);
    labyrinth->set_short("%^GREEN%^Labyrinth%^RESET%^");
    labyrinth->set_long (wrap(
      "All around you, your movements echo throughout the vast expanses of the labyrinth. \
Decaying vines pock the area, concealing exits and perceived exits.  You have a difficult \
journey ahead of you.\n", 72));
    labyrinth->set_entrance(wrap("Your lungs draw breath, albeit in an air that differs \
from your mortal existence.  You are now in the labyrinth.  If you intend to assume your \
previous life, you must somehow find your way out of this place...\n", 72));
    connect_rooms(labyrinth, start_room, "live", "", 1);
}

object query_start_room(){/* return the default room */
    return start_room;
}

object query_meat_locker(){/* return meat locker */
    return meat_locker;
}

object query_labyrinth(){/* return labyrinth */
    return labyrinth;
}

object *query_rooms(){/* return rooms */
    return rooms;
}

void connect_rooms(object room1, object room2, string via, varargs string via2, int oneway){/* connect room1 with room2 with exit name via */
    if(!room1->is_room() || !room2->is_room())
	error("Object not a room");

    if(!via2 || !strlen(via2)){/* add in a flipped direction */
	via2 = flip_dir(via);
    }

    room1->add_exit(via, room2);
    if(!oneway)
	room2->add_exit(via2, room1);
    /* exit registrar ?? */
}

object dig_room(string via, varargs string via2, int oneway){
    object room; /* to hold our new room */

    room = clone_object(ROOM);

    connect_rooms(this_player()->query_environment(), room, via, via2, oneway);
    return room;
}


