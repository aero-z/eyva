#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "data_handler.h"
#include <ayelog.h>
#include <exception.h>
#include <eyva.h>

#include <sys/types.h>   // socket types
#include <sys/socket.h>  // sockets
#include <arpa/inet.h>   // inet (3) functions
#include <unistd.h>      // for write, read
#include <cerrno>        // provides errno makro
#include <cstring>       // memset()

#include <cstdio>        // TODO debug

class Network {
	public:
		Network(DataHandler* data_handler, char const* ip, int port);
		~Network(void);
		void poll(void);

	private:
		void pollIn(void);
		void pollOut(void);
		DataHandler* data_handler;
		int sockc;
		fd_set socket_set;
		struct sockaddr_in server_addr;
		struct timeval select_timeout;
		char buffer_in[BUFFER_SIZE];
		char buffer_out[BUFFER_SIZE];
};

#endif

