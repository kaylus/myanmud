/* The more command.
   Still rather primitive.
   Begun by Mobydick, 6-18-94.
*/

#define SYNTAX "Usage: more <filename>\n"

int do_command (string str) {
    if (!str) return fail_msg(SYNTAX);
    if (!absolute_path(str)) {
	str = previous_object()->query_cwd() + str ;
    }
/* Clear out any ., .., or ~ in the string. */
    str = resolve_path(str) ;
    if (file_exists(str)<1) return fail_msg ("No such file: "+str+"\n");

    if (!previous_object()->valid_read(str)) {
	write ("Permission denied to read "+str+"\n") ;
	return 1 ;
    }
    write (":: "+str+" ::\n") ;
    previous_object()->more_file(str) ;
    return 1 ;
}
