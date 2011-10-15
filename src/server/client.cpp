#include "client.h"

Client::Client(int sockfd, char const* ip_name) {
	this->sockfd = sockfd;
	this->ip_name = ip_name;
}

int Client::getSocket(void) {
	return sockfd;
}

char const* Client::getIPName(void) {
	return ip_name;
}
