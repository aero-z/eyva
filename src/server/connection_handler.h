#ifndef _CONNECTION_HANDLER_
#define _CONNECTION_HANDLER_

#include "user.h"

#include <vector>     // for the list of connected users

class ConnectionHandler {
	public:
		ConnectionHandler();
		void process(char*, char const*, int);
	
	private:
		std::vector<User*> users;
};

#endif
