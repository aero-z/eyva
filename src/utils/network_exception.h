#ifndef _NETWORK_EXCEPTION_H_
#define _NETWORK_EXCEPTION_H_

#define TXTBUF 80

class NetworkException {
	public:
		NetworkException(char const*, ...);
		char const* str();
	private:
		char message[TXTBUF];
};

#endif

