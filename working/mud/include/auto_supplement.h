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
       if(users[i]->query_name() == str){
           return users[i]->query_body();
       }
       }
       return nil;
 }
 
 /* this_player() hacked in */
 static object this_player(){
   return ((this_user()->query_body())?this_user()->query_body():this_user());
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

