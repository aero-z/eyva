#ifndef _SERVER_H_
#define _SERVER_H_

#include "client.h"
#include <ayelog.h>             // for handling messages
#include <network_exception.h>  // for various socket errors
#include <io_exception.h>       // for errors with select()

#include <sys/types.h>  // socket types
#include <sys/socket.h> // sockets
#include <arpa/inet.h>  // inet (3) functions
#include <fcntl.h>      // for O_NONBLOCK
#include <unistd.h>     // for write, read

#include <cstdio>       // TODO debugging

 /* This is the maximum amount of bytes that can be stored in the buffer.
  * See doc/data_definition.txt for further information.
  */
#define BUFFER_SIZE 1024

/* Number of clients that we can handle on this server. */ 
#define CLIENTS_MAX = 3

class Server {
	public:
		Server(int);
		void run();
	private:
		ConnectionHandler* connection_handler;
		int sockl;
		struct sockaddr_in server_addr;
		char buffer[BUFFER_SIZE];
};

#endif

