#include "server.h"
#include <network_exception.h>
#include <ayelog.h>

using namespace AyeLog;

int main(int argc, char** argv) {
	verbosity_level = 1;

	try {
		Server* server = new Server(47208);
		while(server->run());
	} catch(NetworkException* e) {
		logf(ERROR_LOG, e->str());
	}
}
