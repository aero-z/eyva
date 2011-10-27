#include "connection_handler.h"

ConnectionHandler::ConnectionHandler(void) {};

/* PUBLIC METHODS */

void ConnectionHandler::process(char* response, char const* request,
		int RESPONSE_BUF) {
	// TODO
	response[0] = 0;
	response[1] = 'y';
	response[2] = 10;
	response[3] = 0;
}

/* PRIVATE METHODS */

