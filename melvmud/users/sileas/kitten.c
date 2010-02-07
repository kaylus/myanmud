/* This demonstrates heartbeats. */

#include <config.h>

inherit OBJECT ;

int i ;

void create() {
set_short ("[35m[1ma gay kitten[0m") ;
set_long ("This is a lovely black kitten with white paws.\n") ;
set_id(({"kitten"})) ;
    if (!clone_num(this_object())) return ;
    set_heart_beat(5) ;
}

void heart_beat() {

    object foo ;

    foo = query_environment() ;
    set_heart_beat(2) ;
    i = !i ;
if (i) foo->catch_tell("The kitten meows.\n") ; else foo->catch_tell("The kitten swishes its tail.\n") ;
}

