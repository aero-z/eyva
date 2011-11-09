#include "postmaster.h"

/**
 * Constructor.
 */
Postmaster::Postmaster(void)
{
	// VOID
}

/**
 * Destructor.
 */
Postmaster::~Postmaster(void)
{
	box_ui.clear();
	box_network.clear();
}


/* PUBLIC METHODS */


/**
 * This method is used to send a message to a postbox (FIFO).
 * @param box The postbox to send the message to.
 * @param msg The message to be sent.
 */
void
Postmaster::send(Box box, char const* msg)
{
	/* Since we don't know what's going to happen with `msg':
	 */
	char* tmp = new char[msglen(msg)];
	memcpy(tmp, msg, msglen(msg));
	identify(box)->push_back(tmp);
}

/**
 * This method is used to get the oldest message out of a postbox (FIFO).
 * The message will be removed from the box.
 * @param msg A pointer to the string to store the message to.
 * @param box The postbox to be checked.
 * @return    The size of the message (msglen()).
 */
size_t
Postmaster::fetch(char* msg, Box box)
{
	memcpy(msg, (*identify(box))[0], msglen((*identify(box))[0]));
	return msglen(msg);
}


/* PRIVATE METHODS */


/**
 * This method resolves a Box enum to the according "box" vector.
 * @param box The box to be resolved.
 */
std::vector<char*>*
Postmaster::identify(Box box)
{
	switch(box) {
		case BOX_UI:
			return &box_ui;
		case BOX_NETWORK:
			return &box_network;
		default:
			return NULL;
	}
}

