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
static create(){
  driver = find_object(DRIVER);
  driver->set_object_manager(this_object());        /* become object manager */
}


/*
 * NAME:        destruct()
 * DESCRIPTION: The given object is about to be destructed, object.c call
 */
void destruct(string owner, object obj){
  	obj->destruct(); /* required to let our object back out of society */
}

/*
 * NAME:        compiling()
 * DESCRIPTION: The given object is about to be compiled
 */
void compiling(string path){
	return;
}

/*
 * NAME:        compiled()
 * DESCRIPTION:   The given object has just been compiled.  If source is non-nil, it was
 * compiled from that string.  Called just before the object is
 * initialized with create(0).
 */
void compile(string owner, object obj, string source, string inherited...){
	return;
}

/*
 * NAME:        compile_lib()
 * DESCRIPTION:   The given inheritable object has just been compiled.  If source is
 * non-nil, it was compiled from that string.
 */
void compile_lib(string owner, string path, string source, string inherited...){
	return;
}

/*
 * NAME:    compile_failed()
 * DESCRIPTION:  An attempt to compile the given object has failed.
 */
void compile_failed(string owner, string path){
	return;
}

/*
 * NAME:   clone()
 * DESCRIPTION:  The given object has just been cloned.  Called just before the object
 * is initialized with create(1).
 */
void clone(string owner, object obj){
	return;
}

/*
 * NAME:   destruct_lib()
 * DESCRIPTION:  The given inheritable object is about to be destructed
 */
void destruct_lib(string owner, string path){
	return;
}

/*
 * NAME:   remove_program()
 * DESCRIPTION:   The last reference to the given program has been removed
 */
void remove_program(string owner, string path, int timestamp, int index){
	return;
}

/*
 * NAME:  path_special()
 * DESCRIPTION: If the standard include file contains the line `# include "AUTO"',
 *	this function is called so a file can be included that depends on
 *	what file is currently being compiled.
 */
string path_special(string compiled){
	return nil;
}

/*
 * NAME:   include()
 * DESCRIPTION:  The file `path' (which might not exist) is about to be included by
 * `from'.
 */
void include(string from, string path){
	return;
}

/*
 * NAME:  touch()
 * DESCRIPTION:  An object which has been marked by call_touch() is about to have the
 * given function called in it.  A non-zero return value indicates that the
 * object's "untouched" status should be preserved through the following
 * call.
 */
int touch(object obj, string function){
	/* upgrade calls should be made here, that would be things in order to update old objects to new objects */

	return 0;
}

/*
 * NAME: forbid_call()
 * DESCRIPTION: Return a non-zero value if `path' is not a legal first argument
 * for call_other().
 */
int forbid_call(string path){
	return 0;
}

/*
 * NAME: forbid_inherit()
 * DESCRIPTION: Return a non-zero value if inheritance of `path' by `from' is not
 * allowed.  The flag `priv' indicates that inheritance is private.
 */
int forbid_inherit(string from, string path, int priv){
	return 0;
}
