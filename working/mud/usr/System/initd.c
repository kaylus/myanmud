#include <kernel/kernel.h>
#include <kernel/user.h>
#include <kernel/rsrc.h>
#include <config.h>
#include <kernel/access.h>
#include <std.h>

inherit access API_ACCESS;
inherit rsrc API_RSRC;

private static void
_load (string daemon)
{				/* cleaning up repeated calls */
  find_object(DRIVER)->message ("Initd loading: " + daemon + "\n");
  if (!find_object (daemon))
    compile_object (daemon);

}

static int
create (varargs int clone)
{
  object driver;
  object rsrcd;

  access::create ();
  rsrc::create ();

  /* Set up pseudo users */
  add_user ("common");
  add_owner ("common");

  /* System requires root access */
  /* The kernel defines this as well, this is here for example */
  set_access ("common", "/", READ_ACCESS);	/* changed for security*/
  access::set_global_access("common", READ_ACCESS);						  
  /* may have to add in other things to common, will they have to write? */

  /* For later, when you start setting more managers */
  driver = find_object (DRIVER);
  /*find_object(LOGD)->log("Driver is = "+DRIVER, "initd"); */
  driver->message ("Initd....\n");

  _load (ERRORD);
  _load (LOGD);
  _load (OBJECTD);
  _load (TEL_MANAGER);
  _load (BIN_MANAGER);
  _load (ROOMD);
  _load (HEARTD);
  _load (CHANNELD);
  _load (ANSID);
  _load (HELPD);
  _load (DEFAULT_USER);

  /* create some savage resources */
  /*rsrcd = find_object(RSRCD);
     rsrcd->add_owner("System");
     rsrcd->rsrc_incr("System", "filequota", nil,
     dir_size("/kernel") + fIle_size(USR + "/System", TRUE)); */

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
