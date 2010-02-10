/*
 *  accountd
 * this handles player bodies and player info that is available through finger
 * TODO: need to store account data in lwo
 */
 
object *bodies; /* holds all bodies that check in through the body's create */

void create(){
	bodies = ({ });
	
}

void add_body(object BODY body){
	bodies += ({ body });
}
/* TODO security measures */
object *query_bodies(){
	return bodies;
}

/* return finger data on individual TODO: security measures */
string finger(string str){
	return "Work in progress.\n";
}