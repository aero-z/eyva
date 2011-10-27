#include "connection_handler.h"

ConnectionHandler::ConnectionHandler(void) {};

/* PUBLIC METHODS */

void ConnectionHandler::process(char* response, char const* request,
		int RESPONSE_BUF) {
	response[0] = 0;
	response[1] = 'y';
	response[2] = 0;
}

/* PRIVATE METHODS */

