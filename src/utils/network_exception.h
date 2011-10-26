#ifndef _NETWORK_EXCEPTION_H_
#define _NETWORK_EXCEPTION_H_

#define EXCEPTION_MSG_BUF 80

class NetworkException {
	public:
		NetworkException(char const*, ...);
		char const* str();
	
	private:
		char message[EXCEPTION_MSG_BUF];
};

#endif

