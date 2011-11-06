#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <cstring>

class
Client
{
	public:
		Client(int socket, char const* ip);
		~Client(void);
		int getSocket(void);
		char const* getIP(void);
	private:
		int socket;
		char* ip;
};

#endif

