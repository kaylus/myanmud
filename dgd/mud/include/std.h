# define TRUE	1
# define FALSE	0

# undef SYS_PERSISTENT

# define OBJECT "/usr/System/lib/object" /* object */
# define WEIGHT "/usr/System/lib/weight" /* weight logic */
# define CONTAINER "/usr/System/lib/container" /* container */
# define STATS "/usr/System/lib/stats" /* stats */
# define HEALTH "/usr/System/lib/health" /* health */
# define COMBAT "/usr/System/lib/combat" /* combat */
# define WEAPON "/usr/System/lib/weapon" /* weapon */
# define SKILLS "/usr/System/lib/skills" /* skills */
# define WEALTH "/usr/System/lib/wealth" /* wealth */
# define PLAY_TOOL "/usr/System/lib/play_tool"
/* player user interface tool,
   not sure if this is proper route, make object
   for easy redirection? */

# define BODY "/usr/System/obj/body" /* body */
# define ROOM "/usr/System/obj/room" /* room */
# define COIN "/usr/System/obj/coin" /* coin */

# define ESC "\033" /* escape character */

# define OBJ_ACCOUNT /* this uses the account as objects
                        system */

# define HEARTD "/usr/common/sys/heartd"
# define LOGD "/usr/System/sys/logd" /* logger */
# define HELPD "/usr/System/sys/helpd" /* helper daemon */
# define ROOMD "/usr/System/sys/roomd" /* room daemon */
