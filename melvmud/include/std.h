/* This file has to exist or the driver isn't happy. I believe it's
   included automatically in the auto object. Anyway, I don't have
   anything to put here... so... */

#define PI 3.1415926

/* Hymael defines */
#define TP this_player()
#define ETP TP->query_environment()
#define TPN this_player()->query_cap_name()
#define TPn this_player()->query_name()
#define TO this_object()


/* Inheritable objects */
#define OBJECT "/inherit/object"
#define CONTAINER "/inherit/container"
#define ROOM "/inherit/room"
#define BOARD "/inherit/board"
#define MONSTER "/inherit/monster"
#define ARMOR "/inherit/armor"
#define WEAPON "/inherit/weapon"
#define BODY "/inherit/body"
#define HEALTH "/inherit/health"
#define CORPSE "/inherit/corpse"
#define COMBAT "/inherit/combat"
#define WEIGHT "/inherit/weight"
#define WEALTH "/inherit/wealth"
#define STATS "/inherit/stats"
#define SKILLS "/inherit/skills"
#define SHIP "/inherit/ship"
#define SHIP_ROOM "/inherit/ship_room"
#define LIMB "/inherit/limb"
#define PORTAGE "/inherit/portage"
#define COIN "/inherit/coin"

/* Critical messages */
#define DEATHMESS "/doc/news/death"

/* Critical locations in the world */
#define START "/world/start"
#define VOID "/world/void"
#define LABYRINTH "/world/labyrinth"

/* direction mappings */
#define DIRS ([ "east" : "west", "south" : "north", "west" : "east", "north" : "south" ])
#define A_DIRS ({ "east", "west", "south", "north" })
