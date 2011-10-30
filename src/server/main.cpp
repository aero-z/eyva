#include "server.h"
#include <network_exception.h>
#include <io_exception.h>
#include <ayelog.h>
#include <cstdio>

int main(int argc, char **argv) {
	// TODO parse user input

	AyeLog::log_verbosity = 2; // normal log

	printf("Type `help' to see a list of available commands.\n\n");

	Server *server = new Server(1251);
	try {
		server->run();
	} catch(NetworkException *e) {
		delete server;
		AyeLog::logf(ERROR_LOG, e->str());
	} catch(IOException *e) {
		delete server;
		AyeLog::logf(ERROR_LOG, e->str());
	}
}
