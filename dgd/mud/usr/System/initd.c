#include <kernel/kernel.h>
#include <kernel/user.h>
#include <kernel/rsrc.h>
#include <config.h>
#include <kernel/access.h>

inherit access API_ACCESS;
inherit rsrc API_RSRC;

#define TEL_MANAGER "/usr/System/sys/telnetd"	/* telnet manager */
#define BIN_MANAGER "/usr/System/sys/binaryd"	/* binary manager */
#define ERRORD "/usr/System/sys/errord"
#define OBJECTD "/usr/System/sys/objectd"
#define HEARTD "/usr/common/sys/heartd"
#define LOGD "/usr/System/sys/logd"

static int
create (varargs int clone)
{
    object driver;
    object rsrcd;

	access::create();
	rsrc::create();

	/* Set up pseudo users */
	add_user("common");     /* Not really needed */
	add_owner("common");    /* Kernel defines it */

	/* System requires root access */
	/* The kernel defines this as well, this is here for example */
	set_access("common", "/", FULL_ACCESS);



    /* For later, when you start setting more managers */
    driver = find_object (DRIVER);
    /*find_object(LOGD)->log("Driver is = "+DRIVER, "initd");*/
driver->message("Initd...\n");


    /* errord */
    if (!find_object (ERRORD))
	compile_object (ERRORD);
driver->message("Initd: errord...\n");
	/* logd */
	if (!find_object (LOGD))
		compile_object(LOGD);
driver->message("Initd: logd...\n");

    /* objectd */
   if(!find_object(OBJECTD))
	compile_object(OBJECTD);
driver->message("Initd: objectd...\n");

    /* telnetd */
    if (!find_object (TEL_MANAGER))
	compile_object (TEL_MANAGER);
driver->message("Initd: telnet manager...\n");

    /* binaryd */
    if (!find_object (BIN_MANAGER))
	compile_object (BIN_MANAGER);
	driver->message("Initd: binary manager...\n");

    /* room daemon */
    if (!find_object (ROOMD))
	compile_object (ROOMD);
	driver->message("Initd: roomd...\n");

    if (!find_object (HEARTD))
        compile_object (HEARTD);
    driver->message("Initd: heartd...\n");

    if (!find_object (HELPD))
	compile_object (HELPD);
	driver->message("Initd: helpd...\n");

	if (!find_object (CHANNELD))
		compile_object (CHANNELD);
	driver->message("Initd: channeld...\n");



    /* create some savage resources */
    /*rsrcd = find_object(RSRCD);
       rsrcd->add_owner("System");
       rsrcd->rsrc_incr("System", "filequota", nil,
       dir_size("/kernel") + fIle_size(USR + "/System", TRUE));*/

}

/* add a prepare_reboot(), and reboot()? */
