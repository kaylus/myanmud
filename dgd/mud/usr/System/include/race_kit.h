/*
 * These are includes for racial/genders of player bodies
 */
 
#include <stats.h>

#define GENDERS ({ "male", "female", "it" }) 
#define SUBJECTIVES ({ "his", "hers", "its" })
#define RACES ({ "human", "elf", "dwarf", "halfling", "half-orc" })
#define MED_HEIGHTS ({ }) /* fill with median heights of races */
/* indexes into MAP_RACES */
#define RACE_ATTRIBUTES 0

#define MAP_RACES ([ RACES[0] : ({ ({ 0, 0 , 0, 0, 0, 0 }) }),\
                     RACES[1] : ({ ({ -2, -2, +4, +2, 0, +1 }) }),\
	             RACES[2] : ({ ({ +2, +2, -3, 0, +1, -3 }) }),\
		     RACES[3] : ({ ({ -3, +1, +3, +1, 0, 0 }) }),\
		     RACES[4] : ({ ({ +4, +2, -2, -3, -1, -3 }) }) ])
/* contain in here mods for different racial attributes */
