/****************************
 *  heart beat daemon       *
 *  /usr/Common/heartd.c    *
 *  issues event wide pulse *
 ***************************/

#define HB "heart_beat"
#define HB_LENGTH 3

int paused;   /* whether the beat is paused */

void vector_heart_beat(){/* pulse, and revector */
    if(paused) return;

    event(HB); /* propogate event */
    call_out("vector_heart_beat", HB_LENGTH); /* vector */
}

void create(varargs int clone){
    add_event(HB);
    paused=0;
    vector_heart_beat();
}

int query_paused(){ return !!paused; }
void set_paused(int val){ paused = val; }

object *query_sentients(){/* get a list of objects beating */
    return query_subscribed_event(HB);
}

int allow_subscribe(object obj, string name){
    /*if(!sscanf(object_name(obj), "%*s#%*s"))return 0;/* only cloned objects need heartbeats? */
    return 1;/* cull out non body issues? */
}

/* api is for a on creation, a body subscribes to HEARTD and have
   a function in it that is evt_heart_beat */
