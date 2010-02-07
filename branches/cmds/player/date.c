/* return the current date and time via the ctime() kfun.
   Mobydick, 5-28-94 */

int do_command (string str) {
    write ("The current time and date is "+ctime(time())+"\n") ;
    return 1 ;
}

string help(){
	return "Usage: date\n\n\
This command displays the current date and time.";
}