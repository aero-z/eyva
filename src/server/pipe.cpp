#include "pipe.h"

/**
 * Constructor.
 */
Pipe::Pipe(void)
{
	// VOID
}

/** 
 * Destructor.
 */
Pipe::~Pipe(void)
{
	// TODO
}


/* PUBLIC METHODS */


/**
 * This method gets the oldest message in the box (FIFO).
 * @param msg A pointer to the string to store the message to.
 * @return    The size of the message.
 */
size_t
Pipe::fetch(char* msg)
{
	if(!box.empty()) {
		memcpy(msg, box[0], msglen(box[0]));
		box.erase(box.begin());
		return msglen(box[0]);
	}
	return 0;
}

/**
 * This method adds a message to the box (FIFO).
 * @param msg The message to be added to the box.
 */
void
Pipe::add(char const* msg)
{
	box.push_back(msg);
}

/**
 * @return True if there are messages in the box, otherwise false.
 */
bool
Pipe::check(void)
{
	return(box.size() > 0);
}

