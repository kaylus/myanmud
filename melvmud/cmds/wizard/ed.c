/* Hack hack hack.
   Mobydick accepts responsibility, 6-9-1994.
*/

#define SYNTAX "Usage: ed <filename>\n"

int do_command (string str) {
    if (!str) {
	str = this_player()->query_cwf() ;
	if (!str) return fail_msg (SYNTAX);
	}
    if (!absolute_path(str)) {
	str = previous_object()->query_cwd() + str ;
    }
/* Clear out any ., .., or ~ in the string. */
    str = resolve_path(str) ;
/* We don't send ed paths with / on front. */
    if (str[0]=='/') str = str[1..] ;
    if (file_exists(str)==-1) {
	write ("Cannot edit a directory.\n") ;
	return 1;
    }
    previous_object()->set_cwf(str) ;
    previous_object()->edit_file(str) ;
    return 1 ;
}
