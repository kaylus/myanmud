/*
 * Hymael - table
 */

#include <config.h>

#define TO_WIN 100
#define IN_PROGRESS 1
#define OPEN_CHALLENGE 0
#define MAX_SCORES 40
#define SCORES "/users/hymael/obj/scores/tablescores"

inherit OBJECT;


int cprogress, aprogress;
object current_challenger,current_challenged;

int in_use;

/*int log_match(string);*/
/*int struggle(object, object);
/*int scores();*/
/*int next_round();
/*int challenge(string);*/
/*int return_burst(object);
int do_win(object, object);
/*int accept_challenge(string);*/

void create(){
    set_id(({"table"})) ;
    set_short("an arm wrestling table");
    set_long("This is an arm wrestling table.\n");
    in_use=OPEN_CHALLENGE;
    add_command("challenge", "challenge");
    add_command("accept", "accept_challenge");
}
int return_burst(object burster) {
    /*mapping stats=burster->query("stat");
    return (int)(stats["strength"]*random(3)/4)+
    (stats["dexterity"]*random(2)/3)+random(4);*/
    return random(9);
}
int do_win(object winner, object loser) {
    string lname, wname;
    lname = loser->query_cap_name();
    wname = winner->query_cap_name();
    winner->catch_tell("You crushed and defeated "+lname+"!\n");
    loser->catch_tell(wname+" pulverized you!\n");/*
    message(MSG_COMMAND,sprintf("You crushed and defeated %s!\n", lname),
      winner);
    message(MSG_COMMAND,sprintf("%s pulverized you!\n", wname),
      loser);
    message(MSG_COMMAND, sprintf("%s has triumphed over %s!\n", wname,
        lname), environment(TO), ({ winner, loser }));
    log_match(sprintf("%s defeated %s\n", wname, lname));*/
    return 1;
}
int challenge(string challenged) {
    string cname, aname;
    if(!challenged) {
        write("Challenge someone.\n");
        return 1;
    }
    if(query_environment()->present(challenged) && in_use==OPEN_CHALLENGE) {
        current_challenged=USERS_D->find_user(challenged);
        if(!current_challenged) {
            write("Try a living object for more competition.\n");
            return 1;
        }
        current_challenger=TP;
        write("You challenge "+capitalize(challenged)+" to an arm wrestling match!\n");
        say(TPN+" has challenged you to an arm wrestling match!\n");
        /*message(MSG_COMMAND, sprintf("%s challenges %s to an arm wrestling match!\n", TPN,
            capitalize(challenged)),
          environment(TO), ({ current_challenger, current_challenged }));
        */
        return 1;
    }
    else if(in_use==IN_PROGRESS) {
        cname=current_challenger->query_cap_name();
        aname=current_challenged->query_cap_name();
        write("Match in progress between "+cname+" and "+aname+".\n");
    }
    else {
        write(capitalize(challenged)+" is not here.\n");
    }
    return 1;
}
int struggle(object winner, object loser) {
    string lname, wname;
    wname = winner->query_cap_name();
    lname = loser->query_cap_name();
    winner->catch_tell("You press "+lname+"'s hand downward!\n");
    loser->catch_tell(wname+" inches your hand toward defeat!\n");
    /*message(MSG_COMMAND, sprintf("You press %s's hand downward!\n",lname), winner);
    message(MSG_COMMAND, sprintf("%s inches your hand toward defeat!\n",wname), loser);
    message(MSG_COMMAND, sprintf("%s gains the upper hand over %s!\n", wname, lname),
      environment(TO), ({ winner, loser }));*/
    return 1;
}
int next_round() {
    /*here we struggle and keep calling next_round till a winner is found*/
    int challenger_boost;
    int challenged_boost;
    challenger_boost=return_burst(current_challenger);
    challenged_boost=return_burst(current_challenged);

    if(challenger_boost==challenged_boost) {/*equal effort*/
        current_challenger->catch_tell("You fight a stalemate.\n");
        current_challenged->catch_tell("You fight a stalemate.\n");
        /*message(MSG_COMMAND, "You fight a stalemate.\n",
          ({ current_challenged, current_challenger }));
        message(MSG_COMMAND, sprintf("%s fights a stalemate with %s.\n",
            current_challenged->query("cap_name"),current_challenger->query("cap_name")),
          environment(TO), ({ current_challenger, current_challenged }));*/
    } else if(challenger_boost>challenged_boost) {/*challenger winning*/
       struggle(current_challenger, current_challenged);
    } else { /*challenged winning*/
   	struggle(current_challenged, current_challenger);
    }
    aprogress+=challenged_boost;
    cprogress+=challenger_boost;
    if(aprogress>=TO_WIN && cprogress>=TO_WIN) { /*we have a tie*/
 	  	current_challenged->catch_tell("You tied with "+current_challenger->query_cap_name()+".\n");
    	current_challenger->catch_tell("You tied with "+current_challenged->query_cap_name()+".\n");/*
    	message(MSG_COMMAND,sprintf("You tied with %s.\n", current_challenged->query("cap_name")),
          current_challenger);
        message(MSG_COMMAND,sprintf("You tied with %s.\n", current_challenger->query("cap_name")),
          current_challenged);
        message(MSG_COMMAND,sprintf("%s and %s tied.\n", current_challenger->query("cap_name"),
            current_challenged->query("cap_name")),
          environment(TO), ({ current_challenged, current_challenger }));
        log_match(sprintf("%s tied with %s\n",
            current_challenger->query("cap_name"),
            current_challenged->query("cap_name")));*/
        in_use=OPEN_CHALLENGE;
        return 1;
    }
    else if(aprogress>=TO_WIN) { /*challenged won*/

        do_win(current_challenged, current_challenger);
        in_use=OPEN_CHALLENGE;
        return 1;
    }
    else if(cprogress>=TO_WIN) {
        do_win(current_challenger, current_challenged);
        in_use=OPEN_CHALLENGE;
        return 1;
    }
    call_out("next_round",2);
    return 1;
}
int accept_challenge(string acceptance) {
    string cname, aname;
    object challenger;
    if(!acceptance || !current_challenger /*|| !query_environment()->present(current_challenger)*/) {
        write("Accept someone.\n");
        return 1;
    }
    challenger=USERS_D->find_user(acceptance);
    if(!challenger) {
        write("Try a living object for more competition.\n");
        return 1;
    }
    cname=current_challenger->query_cap_name();
    aname=current_challenged->query_cap_name();
    if(in_use==IN_PROGRESS) {
        write("Match in progress between "+cname+" and "+aname+".\n");
        return 1;
    }
    if(1/*challenger==current_challenger /*&& TP==current_challenged /*&& query_environment()->present(current_challenger)*/) {
        in_use=IN_PROGRESS;
        write("You accept "+cname+"'s challenge!\n");
        current_challenger->catch_tell(aname+" has accepted your challenge!\n");
        /*message(MSG_COMMAND, sprintf("%s accepts %s's challenge!\n", aname, cname),
          environment(TO), ({ current_challenger, current_challenged }));
        //call_out to next_round*/
        aprogress=0;
        cprogress=0;
        call_out("next_round", 1); /*start the chain of struggling*/
        return 1;
    }

    write("Accept nothing?\n");
    return 1;
}



/*
int log_match(string logthis) {
    string file, *lines;
    file = read_file(SCORES);
    lines = explode(file, "\n");
    lines = lines[1..MAX_SCORES];
    file = implode(lines, "\n");
    write_file(SCORES, file+"\n"+logthis, 1);
}
int scores() {
    write("Scores:\n\n");
    write(read_file(SCORES));
    return 1;
}*/
