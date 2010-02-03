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
#define HB_TIME 10 /**< default time of ticks */

object _maindeck;        /**< the maindeck */
object _helm;            /**< piloting of the ship */
object _foredeck;        /**< front of the ship */
object _quarterdeck;     /**< back of ship */
object _crowsnest;       /**< crow's nest */

object *_ship;           /**< all ship's rooms */
object docked;           /**< present dock room nil default */


string _ship_name;       /**< name of ship */

int *_coords;            /**< present location of this ship */
int *_heading;           /**< ship's present heading, starts with nowhere */
int _anchored;           /**< anchored or not */
mixed _slider;

/** set up ship */
void create(varargs int clone){
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
    object heartd;

    _ship = allocate(5);
    _ship[MAIN] = _maindeck;
    _ship[HELM] = _helm;
    _ship[FORE] = _foredeck;
    _ship[QUAR] = _quarterdeck;
    _ship[CROW] = _crowsnest;

    _coords = SG_PORT;

    for(i = 5; i--;){
	_ship[i]->set_ship(this_object());
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
    find_object("/usr/System/sys/sea_d")->ship_enter(this_object(), _coords);
    /* ticker */
    heartd = find_object(HEARTD);
    if(!heartd)heartd = compile_object(HEARTD);

    subscribe_event(heartd, "heart_beat");
}

void entre(int *coords){
    _coords = coords;
}

void set_maindeck(object file){
    _maindeck = file;
}

mixed query_main(){ return _ship[MAIN]; }

void set_helm(object file){
    _helm = file;
}

void set_foredeck(object file){
    _foredeck = file;
}

void set_quarterdeck(object file){
    _quarterdeck = file;
}

void set_crowsnest(object file){
    _crowsnest = file;
}

/****************************************
				   [nest] [plank]
			     ||  /
[helm]-[quarterdeck]-[maindeck]-[foredeck]

 possibly cargo holds below

 ****************************************/

/** this is the boat global channel */
mixed ahoy(string str, varargs object exempt){
    int i;
    string mess;


    mess = "";
    if(!str)
	return "Usage: ahoy <message>\n";

    str = capitalize(str);
    if(exempt){
	mess = str;
    }else if(previous_program() != "/usr/System/obj/ship_room"){
	mess = str;
	exempt = nil;
    }else{
	mess += this_player()->query_Name() + " ahoys, \""+str+"\"\n";
	exempt = this_player();
    }
    i = sizeof(_ship);
    while(i--){
	_ship[i]->message(mess, ({ exempt }));
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
    room->set_plank(this_object());
    _ship[MAIN]->message("The gangplank is quickly lowered.\n");
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

    if(!(room = find_object("/usr/System/sys/sea_d")->query_coords(_coords)))
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
	docked->raise_plank(this_object());
	docked = nil;
    }else{
	return 0;
    }
    _ship[MAIN]->raise_plank();
    /* put these messages elsewhere? */
    return 1;
}

/** a player can turn the helm port or starboard */
mixed change_heading(string dir){
    int vec, i, sz;
    /************** (0, 0) is anchored
     (-1, 1) (0, 1)  (1, 1)
     (-1, 0) (0, 0)  (1, 0)
    (-1, -1) (0, -1) (1, -1)
     **************/
    /* test heading */
    if(!dir)
	return "Usage: steer <port/starboard>\n";

    if(_heading[H_X] == 0 && _heading[H_Y] == 0)_heading = ({0, 1});/* for now */

    if((vec = member_array(dir, WHEEL_DIRS)) == -1)
	return "Usage: steer <port/starboard>\n";

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
    this_player()->message("Heading set to "+_heading[H_X]+", "+_heading[H_Y]+" cardinal dir is "+CARDINALS[i]+"\n");
    ahoy("You feel the vessel changing directions to "+dir+".\n", this_player());
    return 1;
}

/** eventually check all these for seamanship */
string query_dir(){
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
    /*set_heart_beat(100);*/
    return 1;
}

int raise_anchor(){
    if(docked)/* raise plank first */
	return -1;

    if(!_anchored)
	return 0;

    /* need mechanism to prime heading */
    _anchored = 0;
    /*set_heart_beat(HB_TIME);*/
    return 1;
}

/** moving may be required to have a suitable number of sails at key points to man sails */
void evt_heart_beat(object obj){/* underway, drift, sail, sink... etc. */
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
    err = catch(find_object("/usr/System/sys/sea_d")->ship_move(this_object(), _heading, _coords));
    if(err)
	ahoy(err);
}
