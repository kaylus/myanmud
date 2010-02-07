/* this daemon does some of the random necessary things to keep the mud operating */
#include <config.h>
#include <kernel/tls.h>

inherit tls API_TLS;

static void create() {
    tls::create();
    set_tls_size(1); /* one thread local variable, index 0 */
}

/* TODO: check to make these calls are from a reliable source */
static void set_this_player(object player) {
LOGD->log("Set player to "+object_name(player), "braind");
    set_tlvar(0, player);
}

/* return the current player */
static object this_player() {
    return get_tlvar(0);
}
