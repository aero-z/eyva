#ifndef _CONNECTION_HANDLER_
#define _CONNECTION_HANDLER_

#include "server.h"
#include "client.h"

#include <vector>    // for the list of clients

class ConnectionHandler {
	public:
		ConnectionHandler(Server*);

	private:
		Server* server;
		std::vector<Client*> client_list;
};

#endif
