#ifndef _SERVER_H_
#define _SERVER_H_

#include "client.h"
#include <ayelog.h>
#include <network_exception.h>

#include <vector>
#include <sys/types.h>  // for ??? TODO
#include <sys/socket.h> // for sockets
#include <netinet/in.h> // for inet_addr
#include <arpa/inet.h>  // for inet_ntoa
#include <fcntl.h>      // for fcntl
#include <unistd.h>     // for sleep, write
#include <cstring>      // for strerr
#include <errno.h>      // for errno

#include <cstdio>       // TODO remove

#define BUFFER_SIZE 20

class Server {
	public:
		Server(int);
		bool run();
	private:
		std::vector<Client*> clients;
		void setNonBlocking(int);
		int sockfd;
		int csockfd;
		struct sockaddr_in client_addr;
		socklen_t client_addr_len;
		char buf[BUFFER_SIZE];
};

#endif

