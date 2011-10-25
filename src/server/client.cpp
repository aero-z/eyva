#include "client.h"

Client::Client(int socket) {
	this->socket = socket;
}

int Client::getSocket(void) {
	return socket;
}

