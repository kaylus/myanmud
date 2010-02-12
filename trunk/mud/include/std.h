# define TRUE	1
# define FALSE	0

# define ASTARIA_CLONE /* set this option for astaria clone code */

# ifndef ASTARIA_CLONE

# define BODY_LIB "/usr/common/lib/body"
# define BODY "/usr/common/obj/body" /* body */
# define HEALTH "/usr/common/lib/health" /* health */
# define COMBAT "/usr/common/lib/combat" /* combat */
# define WEAPON "/usr/common/lib/weapon" /* weapon */
# define PLAY_TOOL "/usr/common/lib/play_tool"
# define ARMOR "/usr/common/lib/armor"

# else /* astaria clone combat and shit */

# define BODY_LIB "/usr/common/lib/attic/body"
# define BODY "/usr/common/obj/body" /* body */
# define HEALTH "/usr/common/lib/attic/health" /* health */
# define COMBAT "/usr/common/lib/attic/combat" /* combat */
# define WEAPON "/usr/common/lib/attic/weapon" /* weapon */
# define PLAY_TOOL "/usr/common/lib/attic/play_tool"
# define ARMOR "/usr/common/lib/attic/armor"

# endif

# define WEIGHT "/usr/common/lib/weight" /* weight logic */
# define SKILLS "/usr/common/lib/skills" /* skills */
# define WEALTH "/usr/common/lib/wealth" /* wealth */
# define ALIAS  "/usr/common/lib/alias"  /* aliases */

# define RACE_KIT "/usr/common/lib/race_kit" /* race info */
# define OBJECT "/usr/common/lib/object" /* object */
# define CONTAINER "/usr/common/lib/container" /* container */
# define STATS "/usr/common/lib/stats" /* stats */
/* player user interface tool,
   not sure if this is proper route, make object
   for easy redirection? */

# define LIB_ROOM "/usr/common/lib/room" /* lib room */
# define ROOM "/usr/common/obj/room" /* room */
# define COIN "/usr/common/obj/coin" /* coin */

# define ESC "\033" /* escape character */

# define OBJ_ACCOUNT /* this uses the account as objects
                        system, deprecated */

# define BRAIND "/usr/System/sys/braind" /* to track some things intelligently */
# define HEARTD "/usr/System/sys/heartd"
# define LOGD "/usr/System/sys/logd" /* logger */
# define HELPD "/usr/System/sys/helpd" /* helper daemon */
# define ROOMD "/usr/System/sys/roomd" /* room daemon */
# define CHANNELD "/usr/System/sys/channeld" /* channel daemon */
# define ACCOUNTD "/usr/System/sys/accountd" /* handles account chores */
# define WEATHERD "/usr/common/sys/weatherd" /* weather daemon */
# define THINGD "/usr/System/sys/thingd" /* thing server */

# define TEL_MANAGER "/usr/System/sys/telnetd"	/* telnet manager */
# define BIN_MANAGER "/usr/System/sys/binaryd"	/* binary manager */
# define ERRORD "/usr/System/sys/errord"
# define OBJECTD "/usr/System/sys/objectd"
# define ANSID "/usr/System/sys/ansi_parser"  

# define LIB_LWO      "/usr/common/data/lib_issue"
# define CLONABLE_LWO "/usr/common/data/clonable_issue"
# define HEAVY_ARRAY "/usr/common/obj/heavy_array"
# define ISSUE_LWO   "/usr/common/lib/issue_lwo"

# define BODY_COMMAND "/usr/common/lib/body_command" /* body commands inherit this */
# define BODY_BIN "/usr/common/obj/cmds/"
# define BODY_INPUT "/usr/common/lib/input"

