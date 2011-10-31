#include "main.h"

void cleanUp(void) {
	delete session;
}

int main(int argc, char** argv) {
	// TODO parse user input

	AyeLog::log_verbosity = 0; // no log output

	AyeLog::logf(LOG_DEBUG, "establishing session to 127.0.0.1:1251");
	try {
		session = new Session("127.0.0.1", 1251);
		session->run();
	} catch(Exception* e) {
		AyeLog::logf(LOG_ERROR, "%s", e->str());
	}

	cleanUp();
}
