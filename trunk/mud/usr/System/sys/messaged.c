/*
 *  messaged : does heavy lifting for all player messages
       'a'    Apply a() to the following element.
       'c'    Apply capitalize() to the following element.
	   'f'    Call the function defined by the given string
       'j'    Join together the following two elements without inserting
	      a space between them.
       'n'    Ignore this element, as if it were not present.  (Useful
	      in condition construction of messages.)
       'p'    Apply pluralize() to the following element.
       's'    Apply singularize() to the following element.
       'w'    Apply capitalize_words() to the following element.

 */
#include <type.h>

string *vowels;
string *outer_calls; /* this holds the calls that occur outside of inner arrays */
string *inner_calls; /* this holds the calls that occur inside nested array */

void create(){/* load up deferring array, pluralization structures, etc */
    vowels = VOWELS;
    outer_calls = ([ 'a': "a",
      'c': "capitalize",
      'f': "func",
      'j': "join",
      'n': "ignore",
      'p': "pluralize",
      's': "singularize",
      'w': "capitalize_words"
    ]);
    inner_calls = ([ ]);
}

/* useful string calls */
string join(string a, string b){ return a + b; }/* 'j' */

string func(object obj, string f){ return call_other(obj, f); }/* 'f' */

string get_name(mixed obj){
    if(typeof(obj) == T_STRING){
	return (string)obj;
    }
    
    if(typeof(obj) == T_OBJECT){/* should know whether to properize the noun or not */
	if(obj->query_Name() == obj->query_short())return (string)obj->query_Name();
	
	return obj->query_short();
    }
    error("Error in get_name: wrong type for obj.\n");
}

string a(mixed obj){
    string str;
    
    str = get_name(obj);
    if(sizeof(VOWELS & ({str[0]})))return "an "+str;
    
    if(capitalize(str) == str)return str;
    
    return "a "+str;
}

string pluralize(mixed obj){/* accept object or string to pluralize */
    string str;
    
    str = get_name(obj);
    return str;
}

string list_array(mixed *list, varargs string and){
    
    
}

inner_parse

string emit(object actor, mixed *emitme){/* does all the heavy lifting of messaging */
    string control, me, we, they;/* gets changed as we step through based on control characters */
    int i, sz;
    
    me = they = we = "";/* /* will be our running concatenation */
    
}


