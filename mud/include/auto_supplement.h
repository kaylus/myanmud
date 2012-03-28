 /* additions to auto */
 /*
 *   * NAME:        member_array()
 *     * DESCRIPTION: return the index of the element in the array, or -1
 *       * Taken from Dworkin's auto object.
 *         */
 static int member_array(mixed elt, mixed *arr){
     int i, sz;

     sz = sizeof(arr);
     for(i=0; i<sz; i++){
         if(arr[i] == elt)
             return i;
     }
     return -1;
 }

 /* pad takes a mixed arg, converts to string, and pads it to the desired
 *     length. Left-justify is the default: if the justify arg is 1, it will
 *         be right-justified. */
 static string pad(string str, int size, varargs int justify){
     int i, len;

     len = strlen(str);
     if(len >= size)
         return str[0..size - 1];
     len = size - len;
     for(i=0; i<len; i++){
                 if(justify)
                 str = " "+str;
                 else
                         str += " ";
     }
     return str;
 }
 
/* This is here as a quasi-hack. Something similar to it will be kept. */
/* direction is a string indicated the direction of the move, which is
   printed to the old room. If it's not passed, we assume a teleport,
   and print a different set of messages entirely. silent is an int
   which can be used to suppress printing the messages. */

static string flip_dir(string dir){
    if(member_array(dir, A_DIRS) > -1){
	return DIRS[dir];
    }
    return "";
}

 /* This function capitalizes the first letter of a string. Handy.
 *     Taken from Dworkin's auto object. */
 static string capitalize(string str){
     if(!str)
         return str;

     if(str[0] >= 'a' && str[0] <= 'z')
         str[0] -= 'a' - 'A';

     return str;
 }

 /* lower case a string */
 static string lowercase(string str){
       int x;
       if(!str)
               return str;

       x = strlen(str);

       while(--x >= 0){
               if(str[x] >= 'A' && str[x] <= 'Z')
                       str[x] += 'a' - 'A';
       }
       return str;
 }


 /* wrap function - Hymael */
 static string wrap(string str, int len){
                 string ret;
                 int i, slen;
                 if(len<1)
                         len = 72;

                 ret=""; /* append onto this string */
                 /* start at len and search back for space, place \n
 *                          and then clip and paste
 *                                            */
                 while(strlen(str)>len){
                         for(i=len-1;i>0 && str[i]!=' ';i--);
                         /* i should be a space or 0 */
                         if(i==0)i=len-1;
                         ret+=str[..i]+"\n";
                         str=str[i+1..];
                 }
                 if(str!="")ret+=str;
                 return ret;
 }


 /* find_player */
 static object find_player(string str){
       object *users;
       int i;

       str = lowercase(str);/* lowercase */
     users = users();
     if(!(i = sizeof(users)))
       return nil;

     while(i--){
       if(users[i]->query_user()->query_name() == str){
           return users[i]->query_user()->query_body();
       }
       }
       return nil;
 }
 
 /* this_player() hacked in */
 /*static object this_player(){
   return ((this_user()->query_body()) ? this_user()->query_body():this_user());
 }*/
 
 static object this_player(){
	return find_object(BRAIND)->this_player();
 }
 
/* replace_string - Hymael */
static string
replace_string (string str, string pattern, string replace)
{
  int plen, slen, cursor;
  string ret;

  if (!str)
    return "";

  plen = strlen (pattern);
  if (!pattern || !plen)
    return str;

  slen = strlen (str);

  cursor = -1;
  ret = "";
  while ((slen - (++cursor + plen)) >= 0 && cursor <= (slen - 1))
    {
      if (str[cursor..cursor + plen - 1] == pattern)
        {                       /*found in string */
          ret += str[..cursor - 1] + replace;
          str = str[cursor + plen..];
          cursor = -1;
          slen = strlen (str);
        }
    }
  if (slen != 0)
    ret += str;
  return ret;
}

/* this strips leading and ending characters from a string, defaults to spaces */
static string strip(string str, varargs int stripit){
	int i, sz, slice_start, slice_end;
	
	if(!stripit)
		stripit = ' ';
	
	slice_start=0;
	sz = strlen(str);
	slice_end=sz-1;
	for(sz = strlen(str), i=0;i < sz;i++){/* leading stripit */
		if(str[i] == stripit)slice_start++;
		else break;
	}	
	
	for(i=sz;--i >= 0;){/* ending stripit */
			if(str[i] == stripit)slice_end--;
			else break;
	}	
	return str[slice_start..slice_end];
}
/*
 *http://lostsouls.org/grimoire_diminishing_returns
 *public domain code for diminishing returns
 */
float diminishing_returns(float val, float scale) {
    float mult, trinum;
	
	if(val < 0.0)
        return -diminishing_returns(-val, scale);
    mult = val / scale;
    trinum = (sqrt(8.0 * mult + 1.0) - 1.0) / 2.0;
    return trinum * scale;
}

string article(string str){
	return (sizeof(VOWELS & ({str[0]}))) ? "an" : "a";
}