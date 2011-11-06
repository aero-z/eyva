#include "client.h"

/**
 * Constructor.
 */
Client::Client(int socket, char const *ip)
{
	this->socket = socket;
	this->ip = new char[strlen(ip)+1]; // +1 for \0
	strcpy(this->ip, ip);
}

/**
 * Destructor.
 */
Client::~Client(void)
{
	/* Against memory leaks:
	 */
	delete[] ip;
	ip = NULL;
}

/* PUBLIC METHODS */

/**
 * @return The client's socket file descriptor.
 */
int
Client::getSocket(void)
{
	return socket;
}

/**
 * @return The decimal/dot string representation of the client's IP.
 */
char const *
Client::getIP(void)
{
	return ip;
}

