#ifndef _SESSION_H_
#define _SESSION_H_

#include <ayelog.h>
#include <network_exception.h>
#include <io_exception.h>
#include <eyva_constants.h>

#include <sys/types.h>   // socket types
#include <sys/socket.h>  // sockets
#include <arpa/inet.h>   // inet (3) functions
#include <unistd.h>      // for write, read
#include <cerrno>        // provides errno makro
#include <cstring>       // memset()

#include <cstdio>        // TODO debug

class Session {
	public:
		Session(char const* ip, int port);
		void run(void);

	private:
		void prepareFDSet(void);
		void handleData(void);
		int sockc;
		fd_set socket_set;
		struct sockaddr_in server_addr;
		struct timeval select_timeout;
		char input_buffer[BUFFER_SIZE];
		char output_buffer[BUFFER_SIZE];
};

#endif

