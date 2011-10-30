#ifndef _SERVER_H_
#define _SERVER_H_

#include "client.h"
#include "data_guard.h"
#include <ayelog.h>             // for handling messages
#include <network_exception.h>  // for various socket errors
#include <io_exception.h>       // for errors with select()
#include <eyva_constants.h>     // various values that are used again and again

#include <vector>       // for the list of clients
#include <sys/types.h>  // socket types
#include <sys/socket.h> // sockets
#include <arpa/inet.h>  // inet (3) functions
#include <fcntl.h>      // for O_NONBLOCK
#include <unistd.h>     // for write, read
#include <cstring>      // memset()
#include <cerrno>       // for the "errno" macro
#include <cstdio>       // for user IO

/* Number of clients that we can handle on this server. */ 
#define CLIENTS_MAX 3

class Server {
	public:
		Server(int);
		void run();
	private:
		void copyFirstLine(char *, char const *);
		void prepareFDSet();
		void handleConnection();
		void handleData(int);
		void handleStdInput();
		void handleResponse();
		DataGuard *data_guard;
		int sockl;
		struct sockaddr_in server_addr;  // our server's network properties
		struct sockaddr_in client_addr;  // temporal struct to store client info
		socklen_t client_addr_len;       // ... and it's size
		char input_buffer[BUFFER_SIZE];
		char output_buffer[BUFFER_SIZE];
		char confirmation_byte;
		std::vector<Client *> clients;
		fd_set socket_set;               // set of socket that select() handles
		bool term_signal;                // will be set to true for shutdown
};

#endif

