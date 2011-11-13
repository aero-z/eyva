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
	box.clear();
}


/* PUBLIC METHODS */


/**
 * This method adds a message to the box (FIFO).
 * @param msg The message to be added to the box.
 */
void
Pipe::add(char const* msg)
{
	char* tmp = new char[msglen(msg)];
	memcpy(tmp, msg, msglen(msg));
	box.push_back(tmp);
}

/**
 * This method is gets the oldest message out of the box (FIFO).
 * The message will be removed from the box.
 * @param buf A pointer to the buffer to store the message to (buffer size
 *            should be BUFFER_SIZE).
 * @return    The size of the message.
 */
size_t
Pipe::fetch(char* buf)
{
	if(!box.empty()) {
		memcpy(buf, box[0], msglen(box[0]));
		box.erase(box.begin());
		return msglen(buf);
	}
	return 0;
}

/**
 * @return True if there are messages in the box, otherwise false.
 */
bool
Pipe::check(void)
{
	return(box.size() > 0);
}

