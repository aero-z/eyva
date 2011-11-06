#include "main.h"

/**
 * This function deletes the created objects and should make sure the program
 * does not leave any memory leaks.
 */
void
cleanUp(void)
{
	delete ui;
	delete network;
	delete data_handler;
}

/**
 * The main function.
 * The program loop is running in here.
 * @param argc Number of arguments passed on program invoke.
 * @param argv String array containing the arguments.
 */
int
main(int argc, char** argv)
{
	/* TODO write argument parser
	 */
	char const* ip = "127.0.0.1";
	int port = 1251;

	AyeLog::log_verbosity = 3;   // no log output

	AyeLog::logf(LOG_DEBUG, "creating DataHandler ...");
	/* The data handler manages information and translates commands
	 * appropriately:
	 */
	data_handler = new DataHandler();

	/* The network and UI use the data_handler to communicate with each other
	 * and to let it handle the commands:
	 */
	try {
		AyeLog::logf(LOG_DEBUG, "connecting to %s on port %d", ip, port);
		network = new Network(data_handler, ip, port);
	} catch(Exception* e) {
		AyeLog::logf(LOG_ERROR, "%s", e->str());
		delete data_handler;
		return -1;
	}
	try {
		ui = new NCursesUI(data_handler);
	} catch(Exception* e) {
		AyeLog::logf(LOG_ERROR, "%s", e->str());
		delete network;
		delete data_handler;
		return -1;
	}

	/* Loop. We will check for activitiy on the network layer, then for activity
	 * on userspace level. Finally, we'll see if there was a request to shutdown
	 * the client and end the program:
	 */
	for(bool term_signal = false; !term_signal; ) {
		try {
			network->poll();
			ui->poll(0.1);
			term_signal = data_handler->getTermSignal();
		} catch(Exception* e) {
			AyeLog::logf(LOG_ERROR, "%s", e->str());
			cleanUp();
			return -1;
		}
	}

	cleanUp();
	return 0;
}

