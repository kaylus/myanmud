/**********
 * a ship *
 **********/
#include <sea_grid.h>

#define MAIN 0
#define HELM 1
#define FORE 2
#define QUAR 3
#define CROW 4

#define _ON(x) object_name(x)
#define HB_TIME 10 /* default time of ticks */

#if 1
string _maindeck;        /* the maindeck */
string _helm;            /* piloting of the ship */
string _foredeck;        /* front of the ship */
string _quarterdeck;     /* back of ship */
string _crowsnest;       /* crow's nest */
#endif /* better system? */

object *_ship;           /* all ship's rooms */
object docked;           /* present dock room nil default */


string _ship_name;       /* name of ship */

int *_coords;            /* present location of this ship */
int *_heading;           /* ship's present heading, starts with nowhere */
int _anchored;           /* anchored or not */
mixed _slider;

void create(){/* set up ship */
	_slider = ({ ({  0,  1 }),
	             ({  1,  1 }),
	             ({  1,  0 }),
	             ({  1, -1 }),
	             ({  0, -1 }),
	             ({ -1, -1 }),
	             ({ -1,  0 }),
	             ({ -1,  1 })
		  	  });
}

void create_ship(){
	int i;
	_ship = allocate(5);
	_ship[MAIN] = clone_object(_maindeck);
	_ship[HELM] = clone_object(_helm);
	_ship[FORE] = clone_object(_foredeck);
	_ship[QUAR] = clone_object(_quarterdeck);
	_ship[CROW] = clone_object(_crowsnest);

	_coords = SG_PORT;

	for(i = 5; i--;){
		_ship[i]->set_ship(TO);
	}

	_ship[MAIN]->add_exit("quarterdeck", _ship[QUAR]);
	_ship[MAIN]->add_exit("crowsnest",   _ship[CROW]);
	_ship[MAIN]->add_exit("foredeck",    _ship[FORE]);
	_ship[FORE]->add_exit("maindeck",    _ship[MAIN]);
	_ship[CROW]->add_exit("maindeck",    _ship[MAIN]);
	_ship[QUAR]->add_exit("maindeck",    _ship[MAIN]);
	_ship[QUAR]->add_exit("helm",        _ship[HELM]);
	_ship[HELM]->add_exit("quarterdeck", _ship[QUAR]);

	_heading = ({ 0, 0 });
	_anchored = 1;
	docked = nil;
	"/system/sea_d"->ship_enter(TO, _coords);
	set_heart_beat(HB_TIME); /* base on seamanship? */
}

void entre(int *coords){
	_coords = coords;
}

void set_maindeck(string file){
	_maindeck = file;
}

mixed query_main(){ return _ship[MAIN]; }

void set_helm(string file){
	_helm = file;
}

void set_foredeck(string file){
	_foredeck = file;
}

void set_quarterdeck(string file){
	_quarterdeck = file;
}

void set_crowsnest(string file){
	_crowsnest = file;
}

/****************************************
			           [nest] [plank]
	                     ||  /
[helm]-[quarterdeck]-[maindeck]-[foredeck]

 possibly cargo holds below

 ****************************************/

int ahoy(string str, varargs object exempt){/* this is the boat global channel */
	int i;
	string mess;


	mess = "";
	if(!str)
		return fail_msg("Usage: ahoy <message>\n");

	str = capitalize(str);
	if(exempt){
		mess = str;
	}else if(previous_program() != "/inherit/ship_room"){
		mess = str;
		exempt = nil;
	}else{
		mess += TPN + " ahoys, \""+str+"\"\n";
		exempt = TP;
	}
	i = sizeof(_ship);
	while(i--){
		_ship[i]->room_tell(mess, ({ exempt }));
	}

	return 1;
}

void set_ship_name(string name){
	_ship_name = capitalize(name);
}

string query_name(){ return _ship_name; }

void set_plank(object room){
	/*object h;*/
	docked = room;
	/*h = "/system/users_d"->find_user("hymael");*/
	_ship[MAIN]->set_plank(room);
	/*if(h)h->catch_tell("Shippy: "+object_name(room)+" has been planked.\n");*/
	room->set_plank(TO);
	_ship[MAIN]->room_tell("The gangplank is quickly lowered.\n");
}
/***********************
 * -1 = anchor not set *
 *  0 = not at a port  *
 *  1 = lowered        *
 *  2 = already lowered*
 ***********************/
int lower_plank(){
	object room;
	/* check for anchor */
	if(!_anchored)
		return -1;

	if(docked)
		return 2;

	if(!(room = "/system/sea_d"->query_coords(_coords)))
		return 0;

	set_plank(room);

	/* find room, need device */
	/* lower away */
	return 1;
}

object query_docked(){
	return docked;
}

/*************************
 * rid plank from docked,*
 * nil docked            *
 *  0 = already raised   *
 *  1 = success          *
 *************************/
int raise_plank(){
	if(docked){/* remove plank from room */
		docked->raise_plank(TO);
		docked = nil;
	}else{
		return 0;
	}
	_ship[MAIN]->raise_plank();
	/* put these messages elsewhere? */
	return 1;
}

int change_heading(string dir){/* a player can turn the helm port or starboard */
	int vec, i, sz;
	/************** (0, 0) is anchored
	 (-1, 1) (0, 1)  (1, 1)
	 (-1, 0) (0, 0)  (1, 0)
	(-1, -1) (0, -1) (1, -1)
	 **************/
	 /* test heading */
	if(!dir)
		return fail_msg("Usage: steer <port/starboard>\n");

	if(_heading[H_X] == 0 && _heading[H_Y] == 0)_heading = ({0, 1});/* for now */

	if((vec = member_array(dir, WHEEL_DIRS)) == -1)
		return fail_msg("Usage: steer <port/starboard>\n");

	if(vec == 0)
		vec = -1;

	for(i = DIRS_SIZE; i--;){
		if(_slider[i][H_X] == _heading[H_X] &&
		   _slider[i][H_Y] == _heading[H_Y])
			break;
	}

	i += vec;
	if(i == DIRS_SIZE)
		i = 0;

	if(i < 0)
		i = DIRS_SIZE - 1;

	_heading = _slider[i];
	write("Heading set to "+_heading[H_X]+", "+_heading[H_Y]+" cardinal dir is "+CARDINALS[i]+"\n");
	ahoy("You feel the vessel changing directions to "+dir+".\n", TP);
	return 1;
}

string query_dir(){/* eventually check all these for seamanship */
	int i;
	for(i = DIRS_SIZE; i--;){
			if(_slider[i][H_X] == _heading[H_X] &&
			   _slider[i][H_Y] == _heading[H_Y])
				break;
	}
	if(i < 0)
		return "nowhere";

	return CARDINALS[i];
}

int query_anchor(){
	return _anchored;
}

int lower_anchor(){
	if(_anchored)/* we're presently anchored */
		return 0;

	_anchored = 1;
	_heading = ({ 0, 0 });/* we aren't going anywhere, need mechanism to get heading going,
	                         may contain previous heading then flip on raised anchor
	                         or just default to some odd direction */
	set_heart_beat(100);
	return 1;
}

int raise_anchor(){
	if(docked)/* raise plank first */
		return -1;

	if(!_anchored)
		return 0;

	/* need mechanism to prime heading */
	_anchored = 0;
	set_heart_beat(HB_TIME);
	return 1;
}

/* moving may be required to have a suitable number of sails at key points to man sails */
void heart_beat(){/* underway, drift, sail, sink... etc. */
	string err;
	if(_anchored){/* not going anywhere, may call a function to do something */
		ahoy("The vessel rocks about on the waves while at anchor.\n");/* randomize */
		return;
	}
	/* adjust hb time for seamanship? */
	if(_heading[H_X] == 0 && _heading[H_Y] == 0){/* unanchored, unheaded: drift randomly? */
		return;
	}
	/* move along heading... */
	err = catch("/system/sea_d"->ship_move(TO, _heading, _coords));
	if(err)
		ahoy(err);
}