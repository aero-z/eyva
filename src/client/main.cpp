#include "server.h"

#include <ayelog.h>
#include <network_exception.h>

using namespace AyeLog;

int main() {
	verbosity_level = 1;

	try {
		Server* server = new Server();
		char msg[2];
		msg[0] = 1;
		msg[1] = 2;
		server->transmit(msg);
	} catch(NetworkException* e) {
		logf(WARNING_LOG, "%s", e);
	}
}
