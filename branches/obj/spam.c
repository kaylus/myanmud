/* A test object, far from and displeasing to the hearts of whales. */

#include <config.h>

inherit CONTAINER ;

void create() {
	::create();
    set_short ("a can of Spam") ;
    set_long ("A very nasty and repulsive object.\nYou think you may barf.\n");
    set_id ( ({ "spam", "can", "can of spam" }) ) ;
    set_weight(2);
    set_bulk(10);
    set_capacity(40);
    set_volume(40);
}
