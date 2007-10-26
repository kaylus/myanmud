/*
 *Hymael gutted to minimal
 *
 */

/* TODO: Use macros for insertion and removal from linked list */
/* TODO: suspend system: also suspend input and logins */
/* TODO: possible to call a function in every clone of every inheritor */
/* TODO: same function call functionality in upgrading */


# include <status.h>
# include <type.h>

# include <kernel/kernel.h>
# include <kernel/objreg.h>
# include <kernel/rsrc.h>

inherit objreg API_OBJREG;
inherit rsrc API_RSRC;

object driver;


/*
 * NAME:        create - initialize
 * DESCRIPTION: Initialize object daemon.
 */
static create()
{
  driver = find_object(DRIVER);
  driver->set_object_manager(this_object());        /* become object manager */

}


/*
 * NAME:        destruct()
 * DESCRIPTION: The given object is about to be destructed, object.c call
 */
void destruct(string owner, object obj)
{
  	obj->destruct(); /* required to let our object back out of society */
}
