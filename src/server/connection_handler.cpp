#include "connection_handler.h"

ConnectionHandler::ConnectionHandler(void) {};

/* PUBLIC METHODS */

void process(char const* request, char* response, int RESPONSE_BUF) {
	for(int i = 0; i < 3; i++) {
		response[i] = 0;
	}
}

/* PRIVATE METHODS */

