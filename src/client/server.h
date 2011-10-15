#ifndef _SERVER_H_
#define _SERVER_H_

#include <errno.h>
#include <cstring>

class Server {
	public:
		Server();
		void transmit(char const*);
	private:
		int sockfd;
};

#endif

