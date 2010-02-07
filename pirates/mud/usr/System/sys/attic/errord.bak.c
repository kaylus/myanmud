#include <kernel/kernel.h>
#include <trace.h>

/*
-Fix up the formatting of the errors and make them more readable
-Tell all admins logged in that an error has occurred and if possible
who caused it. You may want to let them later query the error and get the stack.
-Make this work with atomic functions. Remember that you can't write to a file
inside an atomic function so if somebody is catching an error in an atomic
function you can't write to the error log!
 */

void runtime_error(string error, int caught, mixed** trace)
{
  int size, i, len;
  string line, progname, function, str, objname;
  object obj;

  str = error;

  if(caught != 0) {
    str += " [caught]";
  }
  str += " " + ctime(time()) + "\n";

  size = sizeof(trace) - 1;
  for(i = 0; i < size; i++) {
    progname = trace[i][TRACE_PROGNAME];
    len = trace[i][TRACE_LINE];
    if(len == 0) {
      line = "    ";
    } else {
      line = "    " + (string)len;
      line = line[strlen(line) - 4 ..];
    }

    function = trace[i][TRACE_FUNCTION];
    len = strlen(function);
    if(progname == AUTO && i != size - 1 && len > 3) {
      switch(function[..2]) {
      case "bad":
      case "_F_":
      case "_Q_":
        continue;
      }
    }
    if(len < 17) {
      function += "                 "[len..];
    }

    objname = trace[i][TRACE_OBJNAME];
    if(progname != objname) {
      len = strlen(progname);
      if(len < strlen(objname) && progname == objname[.. len - 1]
         && objname[len] == '#') {
        objname = objname[len..];
      }
      str += line + " " + function + " " + progname + " (" + objname
        + ")\n";
    } else {
      str += line + " " + function + " " + progname + "\n";
    }
  }

  send_message("Runtime error: " + str);
  if(caught == 0 && this_user() && (obj=this_user()->query_user())) {
    obj->message(str);
  }
  write_file("/error.log", str);
}

/*
 * NAME:	compile_error()
 * DESCRIPTION:	deal with a compilation error
 * TODO: test this
 */
static void compile_error(string file, int line, string err)
{
    object obj;

	send_message(file += ", " + line + ": " + err + "\n");
	if (this_user() && (obj=this_user()->query_user())) {
	    obj->message(file);
	    file = this_user()->query_name() + " - " + file;
	}
	write_file("/compile.log", file);
}

/*
 * NAME:	atomic_error()
 * DESCRIPTION:	log a runtime error in atomic code
 * TODO: test this, refine
 * if not preceded by a %, print err to user
 * TODO: make it pass to runtime_error with a preceding % so it knows to log it
 */
static void atomic_error(string str, int atom, mixed **trace)
{
    string line, function, progname, objname;
    int i, sz, len;
    object obj;

	if(str[0] == '%'){
		sz = sizeof(trace) - 1;

		str += " [atomic]\n";

		for (i = atom; i < sz; i++) {
			progname = trace[i][TRACE_PROGNAME];
			len = trace[i][TRACE_LINE];
			if (len == 0) {
			line = "    ";
			} else {
			line = "    " + len;
			line = line[strlen(line) - 4 ..];
			}

			function = trace[i][TRACE_FUNCTION];
			len = strlen(function);
			if (progname == AUTO && i != sz - 1 && len > 3) {
			switch (function[.. 2]) {
			case "bad":
			case "_F_":
			case "_Q_":
				continue;
			}
			}
			if (len < 17) {
			function += "                 "[len ..];
			}

			objname = trace[i][TRACE_OBJNAME];
			if (progname != objname) {
			len = strlen(progname);
			if (len < strlen(objname) && progname == objname[.. len - 1] &&
				objname[len] == '#') {
				objname = objname[len ..];
			}
			str += line + " " + function + " " + progname + " (" + objname +
				   ")\n";
			} else {
			str += line + " " + function + " " + progname + "\n";
			}
		}

		if((obj = this_user()))
			obj->message(str);
	}else{
		if((obj = this_user()))
			obj->message(str);
	}
}