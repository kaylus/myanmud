# include "ssh.h"

# define DEBUG SSH_DEBUG

inherit SSH_TRANSPORT;
private inherit SSH_UTILS;


static int client(string str);


/* ========================================================================= *
 *			   Section 1: authentication			     *
 * ========================================================================= */

private int logged_in;		/* already logged in? */

/*
 * NAME:	userauth_banner()
 * DESCRIPTION:	display a banner during the authentication period
 */
private int userauth_banner(string str)
{
    return ::message(make_mesg(SSH_MSG_USERAUTH_BANNER) +
		     make_string(str) +
		     make_string("en"));
}

/*
 * NAME:        ssh_dsa_verify()
 * DESCRIPTION: verify that the signature was created with a given key
 */
private int ssh_dsa_verify(string m, string public_key, string signature)
{
    string p, q, g, y, r, s, s_blob, u, v, w, c;
    int offset, length;
    string format;

    offset = 0;
    format = get_string(public_key, offset); offset += 4 + strlen(format);
    p      = get_mpint(public_key, offset);  offset += 4 + strlen(p);
    q      = get_mpint(public_key, offset);  offset += 4 + strlen(q);
    g      = get_mpint(public_key, offset);  offset += 4 + strlen(g);
    y      = get_mpint(public_key, offset);  offset += 4 + strlen(y);

    if (format != "ssh-dss") {
	/* Invalid public key format. */
	return 0;
    }

    offset = 0;
    format = get_string(signature, offset); offset += 4 + strlen(format);
    s_blob = get_string(signature, offset); offset += 4 + strlen(s_blob);

    if (format != "ssh-dss") {
	/* Invalid signature format. */
	return 0;
    }
    if (strlen(s_blob) != 40) {
	/* The signature blob should be 40 bytes long, two 160 bit integers. */
	return 0;
    }
    r = "\0" + s_blob[ 0..19];
    s = "\0" + s_blob[20..39];

    w = asn_pow(s, asn_sub(q, "\2", q), q);
    u = asn_mult(w, "\0" + hash_sha1(m), q);
    v = asn_mult(w, r, q);

    return asn_cmp(asn_mod(asn_mult(asn_pow(g, u, p),
				    asn_pow(y, v, p),
				    p),
			   q),
		   r) == 0;
}

/*
 * NAME:	userauth()
 * DESCRIPTION:	respond to a userauth service request
 */
static int userauth(string str)
{
    string name, service, method, password;
    int offset;

    switch (str[0]) {
    case SSH_MSG_SERVICE_REQUEST:
	if (get_string(str, 1) == "ssh-userauth" && !logged_in) {
	    ::message(make_mesg(SSH_MSG_SERVICE_ACCEPT) +
		      make_string("ssh-userauth"));
	} else {
	    ::message(make_mesg(SSH_MSG_DISCONNECT) +
		      make_int(SSH_DISCONNECT_SERVICE_NOT_AVAILABLE) +
		      make_string("service not available") +
		      make_string("en"));
	    return MODE_DISCONNECT;
	}
	break;

    case SSH_MSG_USERAUTH_REQUEST:
	if (!logged_in) {
	    offset = 1;                    name = get_string(str, offset);
	    offset += 4 + strlen(name);    service = get_string(str, offset);
	    offset += 4 + strlen(service); method = get_string(str, offset);
	    offset += 4 + strlen(method);

	    if (service == "ssh-connection") {
		switch (method) {
		case "none":
		    ::message(make_mesg(SSH_MSG_USERAUTH_FAILURE) +
			      make_string("publickey,password") +
			      "\0");
		    break;
		case "publickey":
		    if (!str[offset]) {
			/* Testing the water, which algorithm is allowed. */
			string algo;
			string blob;

			algo = get_string(str, offset + 1);
			blob = get_string(str, offset + 1 + 4 + strlen(algo));
			switch (algo) {
			case "ssh-dss":
			    if (SSHD->valid_public_key(name, blob)) {
				::message(make_mesg(SSH_MSG_USERAUTH_PK_OK) +
					  make_string(algo) +
					  make_string(blob));
			    } else {
				::message(make_mesg(SSH_MSG_USERAUTH_FAILURE) +
					  make_string("publickey,password") +
					  "\0");
			    }
			    break;
			default:
			    ::message(make_mesg(SSH_MSG_USERAUTH_FAILURE) +
				      make_string("publickey,password") +
				      "\0");
			    break;
			}
		    } else {
			string algo;
			string publickey;
			string signature;
			string data;

			offset++;
                        algo = get_string(str, offset);
			offset += 4 + strlen(algo);
			publickey = get_string(str, offset);
			offset += 4 + strlen(publickey);
			signature = get_string(str, offset);

			/*
			 * Signature is made from this data:
			 *
			 * string    session identifier
			 * byte      SSH_MSG_USERAUTH_REQUEST
			 * string    user name
			 * string    service
			 * string    "publickey"
			 * boolean   TRUE
			 * string    public key algorithm name
			 * string    public key to be used for authentication
			 */
			data =
			    make_string(query_session_id()) +
			    make_mesg(SSH_MSG_USERAUTH_REQUEST) +
			    make_string(name) +
			    make_string(service) +
			    make_string("publickey") +
			    "\1" +
			    make_string("ssh-dss") +
			    make_string(publickey);

			if (SSHD->valid_public_key(name, publickey) &&
			    ssh_dsa_verify(data, publickey, signature)) {
			    if (ssh_get_user(name)) {
				logged_in = TRUE;
				ssh_do_login();
				::message(make_mesg(SSH_MSG_USERAUTH_SUCCESS));
			    } else {
				/* no such user? */
				::message(make_mesg(SSH_MSG_USERAUTH_FAILURE) +
					  make_string("publickey,password") +
					  "\0");
				return MODE_DISCONNECT;
			    }
			} else {
			    ::message(make_mesg(SSH_MSG_USERAUTH_FAILURE) +
				      make_string("publickey,password") +
				      "\0");
			}
		    }
		    break;
		case "password":
		    if (!str[offset]) {
			password = get_string(str, offset + 1);
			if (ssh_get_user(name) && ssh_check_password(password))
			{
			    logged_in = TRUE;
			    ssh_do_login();
			    ::message(make_mesg(SSH_MSG_USERAUTH_SUCCESS));
			    break;
			}
			DEBUG(0, "login failed for " + name);
			::message(make_mesg(SSH_MSG_USERAUTH_FAILURE) +
				  make_string("publickey,password") +
				  "\0");
			if (!ssh_get_user(name)) {
			    /* not allowed to try again */
			    return MODE_DISCONNECT;
			}
			break;
		    }
		    ::message(make_mesg(SSH_MSG_USERAUTH_FAILURE) +
			      make_string("publickey,password") +
			      "\0");
		    break;
		default:
		    break;
		}
	    }
	}
	break;

    default:
	if (logged_in) {
	    return client(str);
	}
	break;
    }

    return MODE_NOCHANGE;
}


/* ========================================================================= *
 *			  Section 2: connection layer			     *
 * ========================================================================= */

private int channel;		/* channel ID */
private int window_size;	/* transmit window */
private int packet_size;	/* maximum packet size */
private int program;		/* program started? */

/*
 * NAME:	message()
 * DESCRIPTION:	send a message to the client
 */
atomic int message(string str)
{
    int keep_sending;

    if (channel >= 0 && window_size >= strlen(str)) {
	window_size -= strlen(str);
	keep_sending = TRUE;
	while (strlen(str) > packet_size) {
	    keep_sending &= ::message(make_mesg(SSH_MSG_CHANNEL_DATA) +
				      make_int(channel) +
				      make_string(str[.. packet_size - 1]));
	    str = str[packet_size ..];
	}
	return keep_sending & ::message(make_mesg(SSH_MSG_CHANNEL_DATA) +
					make_int(channel) +
					make_string(str));
    }
}

/*
 * NAME:	client()
 * DESCRIPTION:	handle a client message
 */
static int client(string str)
{
    int offset, channel_id;
    string type;

    switch (str[0]) {
    case SSH_MSG_GLOBAL_REQUEST:
	type = get_string(str, 1);
	offset = strlen(type) + 5;
	if (str[offset]) {
	    ::message(make_mesg(SSH_MSG_REQUEST_FAILURE));
	}
	break;

    case SSH_MSG_CHANNEL_OPEN:
	type = get_string(str, 1);
	offset = 12;
	channel_id = get_int(str, offset);
	offset += 4;
	if (type != "session") {
	    ::message(make_mesg(SSH_MSG_CHANNEL_OPEN_FAILURE) +
		      make_int(channel_id) +
		      make_int(SSH_OPEN_UNKNOWN_CHANNEL_TYPE) +
		      make_string("unknown channel type") +
		      make_string("en"));
	    break;
	}
	if (channel >= 0) {
	    ::message(make_mesg(SSH_MSG_CHANNEL_OPEN_FAILURE) +
		      make_int(channel_id) +
		      make_int(SSH_OPEN_RESOURCE_SHORTAGE) +
		      make_string("out of channels") +
		      make_string("en"));
	    break;
	}

	channel = channel_id;
	window_size = get_int(str, offset);
	offset += 4;
	packet_size = get_int(str, offset);
	::message(make_mesg(SSH_MSG_CHANNEL_OPEN_CONFIRMATION) +
		  make_int(channel_id) +
		  make_int(channel_id) +
		  make_int(0xffffffff) +
		  make_int(2048));
	break;

    case SSH_MSG_CHANNEL_CLOSE:
	if (get_int(str, 1) == channel) {
	    ::message(make_mesg(SSH_MSG_CHANNEL_CLOSE) +
		      make_int(channel));
	    channel = -1;
	    program = FALSE;
	}
	break;

    case SSH_MSG_CHANNEL_WINDOW_ADJUST:
	if (get_int(str, 1) == channel) {
	    window_size += get_int(str, 5);
	}
	break;

    case SSH_MSG_CHANNEL_DATA:
	if (get_int(str, 1) == channel && program) {
	    str = get_string(str, 5);
	    sscanf(str, "%s\r\n", str);
	    sscanf(str, "%s\n", str);
	    return user_input(str);
	}
	break;

    case SSH_MSG_CHANNEL_REQUEST:
	channel_id = get_int(str, 1);
	type = get_string(str, 5);
	offset = strlen(type) + 9;
	if (channel_id == channel && type == "shell" && !program) {
	    program = TRUE;
	    if (str[offset]) {
		::message(make_mesg(SSH_MSG_CHANNEL_SUCCESS) +
			  make_int(channel_id));
	    }
	} else if (str[offset]) {
	    ::message(make_mesg(SSH_MSG_CHANNEL_FAILURE) +
		      make_int(channel_id));
	}
	break;

    case SSH_MSG_CHANNEL_EXTENDED_DATA:
    case SSH_MSG_CHANNEL_EOF:
	break;	/* ignore */

    default: 
	::message(make_mesg(SSH_MSG_UNIMPLEMENTED) +
		  make_int(recv_seqno()));
	break;
    }

    return MODE_NOCHANGE;
}

/*
 * NAME:	create_ssh()
 * DESCRIPTION:	initialize secure shell
 */
static void create_ssh()
{
    create_transport();
    channel = -1;
}
