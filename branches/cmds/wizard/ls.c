/* The all-important ls command.
   Mobydick, 5-29-94.
*/

#define LOADED "[32;1m"
#define DIREC  "[34;1m"
#define RESET  "[0m"

int do_command(string str){
    string directory, workdir, color;
    mixed *files;
    int i, size, cursor;

    if(!str){
       	directory = TP->query_cwd();
    }else{
		if(absolute_path(str)){
	    	directory = str;
        }else{
	    	directory = TP->query_cwd() + "/" + str;
		}
		directory = resolve_path(directory);
    }
    if(directory == "")
    	directory = "/";

    i = file_exists(directory);
    if(!i || i == 1){
        write("No such directory: "+directory+"\n");
		return 1;
    }
    if(!TP->valid_read(directory)){
		write("Permission denied to ls "+directory+"\n");
		return 1;
    }
    i = strlen(directory) - 1;
    workdir = directory;
    if(directory[i] == '/')
    	workdir += "*";
    else
    	workdir += "/*";

    files = get_dir(workdir);
    write(sizeof(files[0])+" files:\n");
    for(i=0; i<sizeof(files[0]); i++){
        if(files[1][i] == 0)
 	    	size = 0;
        else if(files[1][i] == -2)
	    	size = 1;
        else
        	size = (files[1][i] + 999) / 1000;

		str = files[0][i];
		cursor = strlen(str) - 3;
		color = (find_object("/"+directory+str[..cursor])) ? LOADED : "";
        if(files[1][i] == -2){
        	str += "/";
        	color = DIREC;
		}
		str = color+size+" "+str;
		while(strlen(str) < 20 + strlen(color))
			str += " ";

        write(str+RESET);
		if(i % 4 == 3)
			write("\n");

    }
    if(sizeof(files[0]) % 4 > 0)
    	write("\n");

    return 1;
}
