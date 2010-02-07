/* Eval command
   Forms up a file with commands given and executes
   -Hymael
*/

#include <options.h>
#include <config.h>

#define SYNTAX "Usage: eval <statements>\n"

int do_command (string str) {
    string code, filename;
    object obj;
    if(!str)return fail_msg(SYNTAX);
    filename="/users/hymael/temp";
    remove_file(filename);
    code = "# include <float.h>\n# include <limits.h>\n" +
		  "# include <status.h>\n# include <trace.h>\n# include <config.h>\n" +
		  "# include <type.h>\n\n" +
		  "void exec() {\n" +
		  "    mixed a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;\n\n" +
	  "    " + str + "\n}\n";
	rlimits(-1;-1){
	str = catch(obj = compile_object(filename, code),
				obj->exec());
	if(str){
		write("Error: "+str+"\n");
		write(code);
	}
	if(obj) destruct_object(obj);
	}
	return 1;
}

string help(){
	return SYNTAX+"\n\
This command evaluates LPC code.\n";
}

/*static void cmd_code(object user, string cmd, string str)
{
    mixed *parsed, result;
    object obj;
    string name;

    if (!str) {
	message("Usage: " + cmd + " <LPC-code>\n");
	return;
    }

    parsed = parse_code(str);
    name = USR + "/" + owner + "/_code";
    obj = find_object(name);
    if (obj) {
	destruct_object(obj);
    }
    if (!parsed) {
	return;
    }

    str = USR + "/" + owner + "/include/code.h";
    if (file_info(str)) {
	str = "# include \"~/include/code.h\"\n";
    } else {
	str = "";
    }
    str = "# include <float.h>\n# include <limits.h>\n" +
	  "# include <status.h>\n# include <trace.h>\n" +
	  "# include <type.h>\n" + str + "\n" +
	  "mixed exec(object user, mixed argv...) {\n" +
	  "    mixed a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;\n\n" +
	  "    " + parsed[0] + "\n}\n";
    str = catch(obj = compile_object(name, str),
		result = obj->exec(user, parsed[1 ..]...));
    if (str) {
	message("Error: " + str + ".\n");
    } else {
	store(result);
    }

    if (obj) {
	destruct_object(obj);
    }
}*/
