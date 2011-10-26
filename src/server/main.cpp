#include "server.h"
#include <network_exception.h>
#include <io_exception.h>
#include <ayelog.h>

int main(int argc, char** argv) {
	AyeLog::log_verbosity = 1;

	try {
		Server* server = new Server(47208);
		server->run();
	} catch(NetworkException* e) {
		AyeLog::logf(ERROR_LOG, e->str());
	} catch(IOException* e) {
		AyeLog::logf(ERROR_LOG, e->str());
	}
}
