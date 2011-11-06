#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "client.h"
#include "data_handler.h"
#include <ayelog.h>
#include <exception.h>
#include <eyva.h>     // various values that are used again and again

#include <vector>       // for the list of clients
#include <sys/types.h>  // socket types
#include <sys/socket.h> // sockets
#include <arpa/inet.h>  // inet (3) functions
#include <unistd.h>     // for write, read
#include <cstring>      // memset()
#include <cerrno>       // for the "errno" macro
#include <cstdio>       // for user IO

/* Number of clients that we can handle on this server.
 * TODO make this dynamic
 */ 
#define CLIENTS_MAX 3

class
Network
{
	public:
		Network(DataHandler* data_handler, int port);
		~Network(void);
		void poll(void);

	private:
		void pollIn(void);
		void pollOut(void);
		void handleConnection(void);
		void handleData(int id);
		void handleStdInput(void);
		void copyFirstLine(char* dest, char const* src);
		void removeClient(int id);

		DataHandler* data_handler;
		std::vector<Client*> clients;
		std::vector<Client*> targets;    // temporal client list
		fd_set socket_set;               // set of socket that select() handles
		int sockl;
		struct sockaddr_in server_addr;  // our server's network properties
		struct sockaddr_in client_addr;  // temporal struct to store client info
		socklen_t client_addr_len;       // ... and it's size
		char buffer_in[BUFFER_SIZE];
		char buffer_out[BUFFER_SIZE];
		char confirmation_byte;
};

#endif

