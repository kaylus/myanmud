/*
   finger.c
   The finger command, tells you when a user was last on, his real
   name and email address, and so forth.
   It does _not_ restore the user object because the user object
   can be cloned only by the driver object (for security reasons).
   Instead we read the .o file by hand.
   Written by Mobydick, 5-28-94.
*/

#define SYNTAX "Usage: finger <player>\n"

int do_command (string str) {

    int i,bogon, sz;
    string s1,s2 ;
    string *user_file;
    string *player_file ;
    mapping user_data, player_data ;

    /*if(str=="hymael"){
		write("Don't finger god.\n");
		return 1;
	}*/

    if (!str || str=="") return fail_msg(SYNTAX);

    if (file_exists("/data/user/"+str+".dat")<1) {
        return fail_msg("There is no player named "+capitalize(str)+".\n");
	}
    user_file = explode(read_file("/data/user/"+str+".dat"),"\n") ;
    player_file = explode(read_file("/data/player/"+str+".dat"), "\n");
    player_data = ([ ]);
    user_data = ([ ]) ;
    for (i=0,sz=sizeof(user_file);i<sz;i++) {
        if (sscanf(user_file[i],"%s %d",s1,bogon)==2) {
	   user_data[s1]=bogon ;
        } else {
            if (sscanf(user_file[i],"%s %s",s1,s2)==2) {
	        user_data[s1]=s2 ;
	    }
	}
    }
    for (i=0,sz=sizeof(player_file);i<sz;i++) {
	        if (sscanf(player_file[i],"%s %d",s1,bogon)==2) {
		   player_data[s1]=bogon ;
	        } else {
	            if (sscanf(player_file[i],"%s %s",s1,s2)==2) {
		        player_data[s1]=s2 ;
		    }
		}
    }
    /* The formatting is kind of primitive since I haven't written
       any sort of printf() yet. */
    write ("User name:   "+replace_string(user_data["cap_name"],"\"", "")+"\n"+
	   "Real name:   "+replace_string(user_data["real_name"],"\"", "")+"\n"+
	   "Email:       "+replace_string(user_data["email"],"\"", "")+"\n"+
	   "Last on:     "+ctime(user_data["last_on"])+"\n"+
	   "Gender:      "+replace_string(player_data["gender"],"\"", "")+"\n"+
	   "From:        "+replace_string(user_data["last_ip"],"\"", "")+"\n") ;
	if(player_data["wizard"])write("This player is a wizard.\n");
	if(player_data["describe"])
		write("\nDescription:\n"+replace_string(player_data["describe"],"\"", "")+"\n");
    return 1;
}

string help(){
	return SYNTAX+"\n\
This command displays information on the given player.";
}