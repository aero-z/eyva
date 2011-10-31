#include "main.h"

void cleanUp(void) {
	delete server;
}

int main(int argc, char** argv) {
	// TODO parse user input

	AyeLog::log_verbosity = 2; // normal log

	printf("\nType `help' to see a list of available commands.\n\n");

	try {
		server = new Server(1251);
		server->run();
	} catch(Exception* e) {
		AyeLog::logf(LOG_ERROR, e->str());
	}

	cleanUp();
}
