#ifndef _NETWORK_H_
#define _NETWORK_H_

// server
#include <client.h>

// hybrid
#include "postmaster.h"
#include "eyva.h"

// utils
#include <ayelog.h>
#include <exception.h>

// linux
#include <sys/types.h>  // socket types
#include <sys/socket.h> // sockets
#include <arpa/inet.h>  // inet (3) functions
#include <unistd.h>     // for write, read
#include <cerrno>       // for the "errno" macro
#include <vector>
#include <cstring>

/* Number of clients that we can handle in server mode.
 * TODO make this dynamic
 */ 
#define CLIENTS_MAX 3

class
Network
{
	public:
		Network(Postmaster* pm);
		~Network(void);
		void poll(void);

		#ifdef __ESERVER
			void start(int port);
		#else
			void start(char const* ip, int port);
		#endif

	private:
		void pollOut(void);
		void pollIn(void);
		void handleConnection(void);
		void handleData(int id);
		size_t strcpy_fl(char* dest, char const* src);
		void disconnect(int id);

		Postmaster* pm;
		Session* session;
		fd_set socket_set;
		int sockc;
		struct sockaddr_in server_addr;
		char buffer_in[BUFFER_SIZE];
		char buffer_out[BUFFER_SIZE];
		char confirmation_byte;
		#ifdef __ECLIENT
			struct timeval select_timeout;
		#endif
};

#endif

