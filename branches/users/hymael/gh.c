/*
 *  workroom.c
 *  GH
 */

#include <config.h>

inherit ROOM;

void create() {
set_short ("[1m[36mStarkeep Grand Hall[0m") ;
    set_long ("The beauty and splendor of Starkeep's Grand Hall is wondrous and\n"+
                "amazing. The floor and walls are crafted of perfectly polished marble.\n"+
                "Their luster is so great you can nearly see your reflection everywhere.\n"+
                "The ceiling is far above you, and its curved dome creates an odd echoing\n"+
                "effect on everything you say in here. The hall is a truly mind-boggling\n"+
                "and breathtaking room to behold.\n\n"+
                "The Adventurer's Guild is located through an archway eastward.\n"+
                "New adventurers can go below and learn some of the basic\n"+
                "elements of the Realm.\n\n"+
                "[1m[33mThere is a map of Starkeep etched on a gold plaque.\n[0m");
    set_exits ( ([ "start" : "/world/start" ]) ) ;
}
