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
 * @param buf A pointer to the buffer to store the message to (buffer size
 *            should be BUFFER_SIZE).
 * @param box The postbox to be checked.
 * @return    The size of the message (msglen()).
 */
size_t
Postmaster::fetch(char* buf, Box box)
{
	/* See what box is requested:
	 */
	std::vector<char*>* inbox = identify(box);

	/* Check if there's data at all:
	 */
	if(inbox->size() == 0)
		return 0;
	
	/* Copy the data. Use memcpy instead of strcpy, since there is all kinds of
	 * data (also \0 bytes):
	 */
	memset(buf, 0, BUFFER_SIZE);
	memcpy(buf, (*inbox)[0], msglen((*inbox)[0]));
	return msglen(buf);
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

