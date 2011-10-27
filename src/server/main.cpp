#include "server.h"
#include <network_exception.h>
#include <io_exception.h>
#include <ayelog.h>
#include <cstdio>

int main(int argc, char** argv) {
	AyeLog::log_verbosity = 2;

	printf("Type `help' to see a list of available commands.\n\n");

	try {
		Server* server = new Server(1251);
		server->run();
	} catch(NetworkException* e) {
		AyeLog::logf(ERROR_LOG, e->str());
	} catch(IOException* e) {
		AyeLog::logf(ERROR_LOG, e->str());
	}
}
