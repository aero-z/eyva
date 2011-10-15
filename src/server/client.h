#ifndef _CLIENT_H_
#define _CLIENT_H_

class Client {
	public:
		Client(int, char const*);
		int getSocket();
		char const* getIPName();

	private:
		int sockfd;
		char const* ip_name;
};

#endif

