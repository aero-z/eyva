#include "session.h"

using namespace AyeLog;

/**
 * Constructor.
 * @param id   The session ID (= socket file descriptor for this connection).
 * @param ip   The client's IP address.
 * @param pipe A pointer to where answer messages shall be stored to.
 */
Session::Session(int id, char const* ip, Pipe* pipe)
{
	this->pipe = pipe;
	this->id = id;

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
Session::handle(char const* message, int message_len)
{
	// TODO
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
Session::getID(void)
{
	return id;
}

