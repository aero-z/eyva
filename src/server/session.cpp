#include "session.h"

using namespace AyeLog;

/**
 * Constructor.
 * @param id   The session ID (= socket file descriptor for this connection).
 * @param ip   The client's IP address.
 * @param pipe A pointer to where answer messages shall be stored to.
 */
Session::Session(int session_id, char const* ip, Pipe* pipe)
{
	this->pipe = pipe;
	this->session_id = session_id;

	this->ip = new char[strlen(ip)+1]; // +1 for \0
	strncpy(this->ip, ip, strlen(ip));
	this->ip[strlen(ip)] = 0; // terminate (strncpy doesn't do that...)

	//logf(LOG_DEBUG, "> %s: new session on socket %d", ip, id);
}

/**
 * Destructor.
 */
Session::~Session(void)
{
	delete[] ip;
}


/* PUBLIC METHODS */


/**
 * This method handles a message received by the client.
 * @param message     The received message.
 * @param message_len The received message's length.
 */
void
Session::process(char const* message, size_t message_len)
{
	/* TODO
	 * This is temporary, until we've got an admin client:
	 */
	if(message_len == 3 && message[0] == ':' && message[1] == 'q'
			&& message[2] == 10) {
		char response[4] = {0, 0, 0, 0};
		pipe->push(response);
		return;
	}

	/* If the message length does not correspond to the length indicated in the
	 * message, send a [0A FAIL] message back:
	 */
	if(msglen(message) != message_len) {
		char response[4] = {session_id, 10, 0, 0};
		pipe->push(response);
		return;
	}
}

/**
 * @return The IP of this session's client.
 */
char const*
Session::getIP(void)
{
	return ip;
}

/**
 * @return The session ID (and also socket file descriptor).
 */
int
Session::getSessionID(void)
{
	return session_id;
}

