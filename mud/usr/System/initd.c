#include <kernel/kernel.h>
#include <kernel/user.h>
#include <kernel/rsrc.h>
#include <kernel/version.h>
#include <config.h>
#include <kernel/access.h>
#include <std.h>

#include <game/sea_grid.h>

inherit access API_ACCESS;
inherit rsrc API_RSRC;

private static void _load (string daemon){/* cleaning up repeated calls */
    find_object(DRIVER)->message ("Initd loading: " + daemon + "\n");
    if (!find_object (daemon))
	compile_object (daemon);
}

static int create (varargs int clone){
    object driver;
    object rsrcd;

    access::create ();
    rsrc::create ();

    /* adding Common */
    add_owner ("Common");
	add_owner ("Game");

    /* System requires root access */
    /* The kernel defines this as well, this is here for example */
    access::set_global_access("Common", READ_ACCESS);	
    access::set_global_access("Game", READ_ACCESS);
    /* may have to add in other things to common, will they have to write? */

    /* For later, when you start setting more managers */
    driver = find_object (DRIVER);
    driver->message ("Initd....\n");
	
	driver->message("Kernel version: "+KERNEL_LIB_VERSION+"\n");

    _load (ERRORD);
    _load (LOGD);
    _load (OBJECTD);
	OBJECTD->do_initial_obj_setup();
	
    _load (TEL_MANAGER);
    _load (BIN_MANAGER);
    _load (ROOMD);
    _load (HEARTD);
    _load (CHANNELD);
    _load (ANSID);
    _load (HELPD);
    _load (SEA_D);
	_load (BRAIND);
	_load (ACCOUNTD);
	_load (WEATHERD);
    _load (WORLDBANKD);
}
/* called by driver before a reboot */
void prepare_reboot(){
    /* log out players */
    object *users;
    int i;

    find_object(LOGD)->log("Mud is rebooting.", "boot");
    users = users();
    for(i=sizeof(users);i--;){
	users[i]->message("Mud is rebooting...you will be disconnected.\n");
	users[i]->logout(1); 
    }
    /* anything else? */
}
/* called after a reboot */
void reboot(){
    find_object(LOGD)->log("Rebooted", "boot");
}
