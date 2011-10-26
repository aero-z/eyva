#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <cstring>   // for strlen()

class Client {
	public:
		Client(int, char const*);
		~Client();
		int getSocket();
		char const* getIP();
	private:
		int socket;
		char* ip;
};

#endif

