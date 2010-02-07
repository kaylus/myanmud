/* A quaint little people command.
   mobydick, 7-10-94. */

#include <config.h>

#define FILL "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n"

int do_command() {

    string name, room, idlestr, ip, rank ;
    int idle, i, sz;
    object *users ;

    users = USERS_D->query_users() ;
    write (FILL);
    write ("Name            Rank     Idle    IP             Location\n") ;
    write (FILL);
    for (i=0,sz=sizeof(users);i<sz;i++) {
	name = users[i]->query_cap_name() ;
	rank = capitalize(users[i]->query_privileges()) ;
	rank = pad(rank,9) ;
	if (users[i]->query_in_edit()) name = "["+name+"]" ;
	name = pad(name,16) ;
	idle = users[i]->query_idle()/60 ;
	if (idle) idlestr = idle+"m" ; else idlestr ="" ;
	idlestr = pad(idlestr,8) ;
        ip = query_ip_number(users[i]) ;
	if (!ip) ip = "<netdead>" ;
	if (ip=="127.0.0.1")ip="localhost";
	ip = pad(ip,15) ;
	room = object_name(users[i]->query_player()->query_environment()) ;
	write (name+rank+idlestr+ip+room+"\n") ;
    }
    write (FILL);
    return 1 ;
}
