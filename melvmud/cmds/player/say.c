/* The say command.
   Broadcast a message to every living object in the same room.
   Written by Mobydick, 5-27-94.
*/
#include <config.h>

int do_command (string str) {
    object *people;
    string mess;
    int i;
    if(!str || replace_string(str," ","") == ""){
        write("You mumble.\n");
		say(TPN+" mumbles.\n");
        return 1 ;
    }
    write(TP->query_color("say")+"You say, \""+capitalize(str)+"\"[0m\n") ;
    mess = TPN+" said, \""+capitalize(str)+"\"[0m\n";
    people = TP->query_environment()->query_inventory();
    i = sizeof(people);
    while(--i >= 0){
		if(!people[i]->query_living() || people[i] == TP)
			continue;

		people[i]->catch_tell(people[i]->query_color("say")+mess);
		people[i]->add_backlog("say",people[i]->query_color("say")+mess);
	}
    return 1;
}

string help(){
	return "Usage: say <message>\n\n\
This command allows you to address a message to everyone in your\n\
present room.";
}