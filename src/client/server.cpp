#include "server.h"

#include <ayelog.h>
#include <network_exception.h>

#include <sys/types.h>    // for ??? TODO
#include <sys/socket.h>   // for sockets
#include <netinet/in.h>   // for inet_addr
#include <arpa/inet.h>    // for inet_ntoa
#include <cstring>        // for strlen
#include <unistd.h>       // for write

using namespace AyeLog;

Server::Server(void) {
	/* see src/server/server.cpp for further information */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		throw new NetworkException("socket() failed");
	
	struct sockaddr_in server_addr;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // TODO
	server_addr.sin_port = htons(47208); // TODO
	server_addr.sin_family = AF_INET;

	if(connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		throw new NetworkException("connect() failed: %s", strerror(errno));
	}
}

void Server::transmit(const char* msg) {
	if(write(sockfd, (void*)msg, strlen(msg)) >= 0) {
		logf(NORMAL_LOG, "sent: [%d]", msg[0]);
	} else {
		logf(WARNING_LOG, "could not send \"%s\": %s", msg, strerror(errno));
	}
}
