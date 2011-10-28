#include "client.h"

Client::Client(int socket, char const *ip) {
	this->socket = socket;
	int string_length = strlen(ip);
	this->ip = new char[string_length+1];// +1 because we also need to store \0
	for(unsigned int i = 0; i < strlen(ip); i++) {
		this->ip[i] = ip[i];
	}
	this->ip[string_length] = 0;    // terminate string
}

Client::~Client(void) {
	// empty
}

/* PUBLIC METHODS */

int Client::getSocket(void) {
	return socket;
}

char const *Client::getIP(void) {
	return ip;
}

/* PRIVATE METHODS */

