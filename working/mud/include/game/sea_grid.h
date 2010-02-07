/*************
 * Sea grid  *
 *************/
#define SEA_D "/usr/game/sys/sea_d"

#define LIB_SHIP_ROOM "/usr/game/lib/ship_room"
#define SHIP_ROOM "/usr/game/obj/ship_room"
#define LIB_PORTAGE "/usr/game/lib/portage"
#define PORTAGE   "/usr/game/obj/portage"
#define SHIP  "/usr/game/obj/ship"
#define LIB_SHIP "/usr/game/lib/ship"
 
#define X_DIM 10 /**< x dimension */
#define Y_DIM 10 /**< y dimension */

#define H_X 0
#define H_Y 1

#define SG_PORT ({ 0, 5 }) /**< where our port is */

#define WHEEL_DIRS ({ "port", "starboard" }) /**< wheel directions */

#define DIRS_SIZE 8

#define CARDINALS ({ "north", "northeast", "east", "southeast", "south", "southwest", "west", "northwest"})

#define SG_ROOM 0  /* indexes into the grid array */
#define SG_FUNC 1  /* function to be called */
#define SG_OBJ  2  /* object which contains the entering code, defaults to sea daemon */
