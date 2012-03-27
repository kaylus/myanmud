# define TRUE	1
# define FALSE	0

# define ASTARIA_CLONE /* set this option for astaria clone code */

# ifndef ASTARIA_CLONE

# define BODY_LIB "/usr/Common/lib/body"
# define BODY "/usr/Common/obj/body" /* body */
# define HEALTH "/usr/Common/lib/health" /* health */
# define COMBAT "/usr/Common/lib/combat" /* combat */
# define WEAPON "/usr/Common/lib/weapon" /* weapon */
# define PLAY_TOOL "/usr/Common/lib/play_tool"
# define ARMOR "/usr/Common/lib/armor"

# else /* astaria clone combat and shit */

# define BODY_LIB "/usr/Common/lib/attic/body"
# define BODY "/usr/Common/obj/body" /* body */
# define HEALTH "/usr/Common/lib/attic/health" /* health */
# define COMBAT "/usr/Common/lib/attic/combat" /* combat */
# define WEAPON "/usr/Common/lib/attic/weapon" /* weapon */
# define PLAY_TOOL "/usr/Common/lib/attic/play_tool"
# define ARMOR "/usr/Common/lib/attic/armor"

# endif

# define WEIGHT "/usr/Common/lib/weight" /* weight logic */
# define SKILLS "/usr/Common/lib/skills" /* skills */
# define WEALTH "/usr/Common/lib/wealth" /* wealth */
# define ALIAS  "/usr/Common/lib/alias"  /* aliases */

# define RACE_KIT "/usr/Common/lib/race_kit" /* race info */
# define OBJECT "/usr/Common/lib/object" /* object */
# define CONTAINER "/usr/Common/lib/container" /* container */
# define STATS "/usr/Common/lib/stats" /* stats */
/* player user interface tool,
   not sure if this is proper route, make object
   for easy redirection? */

# define LIB_ROOM "/usr/Common/lib/room" /* lib room */
# define ROOM "/usr/Common/obj/room" /* room */
# define COIN "/usr/Common/obj/coin" /* coin */

# define ESC "\033" /* escape character */

# undef TRACKCOINS  /* whether or not to track coins */
# define OBJ_ACCOUNT /* this uses the account as objects
                        system, deprecated */

# define BRAIND "/usr/System/sys/braind" /* to track some things intelligently */
# define HEARTD "/usr/System/sys/heartd"
# define LOGD "/usr/System/sys/logd" /* logger */
# define HELPD "/usr/System/sys/helpd" /* helper daemon */
# define ROOMD "/usr/System/sys/roomd" /* room daemon */
# define CHANNELD "/usr/System/sys/channeld" /* channel daemon */
# define ACCOUNTD "/usr/System/sys/accountd" /* handles account chores */
# define WEATHERD "/usr/Common/sys/weatherd" /* weather daemon */
# define THINGD "/usr/System/sys/thingd" /* thing server */
# define WORLDBANKD "/usr/Common/sys/worldbankd" /* finance tracker */

# define TEL_MANAGER "/usr/System/sys/telnetd"	/* telnet manager */
# define BIN_MANAGER "/usr/System/sys/binaryd"	/* binary manager */
# define ERRORD "/usr/System/sys/errord"
# define OBJECTD "/usr/System/sys/objectd"
# define ANSID "/usr/System/sys/ansi_parser"  

# define LIB_LWO      "/usr/Common/data/lib_issue"
# define CLONABLE_LWO "/usr/Common/data/clonable_issue"
# define HEAVY_ARRAY "/usr/Common/obj/heavy_array"
# define ISSUE_LWO   "/usr/Common/lib/issue_lwo"

# define BODY_COMMAND "/usr/Common/lib/body_command" /* body commands inherit this */
# define BODY_BIN "/usr/Common/obj/cmds/"
# define BODY_INPUT "/usr/Common/lib/input"
# define CMD_PREFIX "cmd_"
# define OBJ_ACTION "perform_action"
# define PER_ACTION mixed perform_action(string verb, varargs string arg)

/* direction mappings */
#define DIRS ([ "east" : "west", "south" : "north", "west" : "east", "north" : "south" ])
#define A_DIRS ({ "east", "west", "south", "north" })
