#ifndef _CLIENT_H_
#define _CLIENT_H_

class Client {
	public:
		Client(int);
		int getSocket();
	private:
		int socket;
};

#endif

