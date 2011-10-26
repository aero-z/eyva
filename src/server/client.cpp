#include "client.h"

Client::Client(int socket, char const* ip) {
	this->socket = socket;
	this->ip = new char[strlen(ip)];
	for(unsigned int i = 0; i < strlen(ip); i++) {
		this->ip[i] = ip[i];
	}
}

Client::~Client(void) {
	// empty
}

/* PUBLIC METHODS */

int Client::getSocket(void) {
	return socket;
}

char const* Client::getIP(void) {
	return ip;
}

/* PRIVATE METHODS */

