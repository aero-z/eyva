#include "main.h"

/**
 * This function makes the program ready to stop.
 */
void
cleanUp(void)
{
	delete network;
	delete game;
	delete data_handler;
}

/**
 * The main function.
 * @param argc The number of arguments given.
 * @param argv A list of arguments given.
 * @return Error code:
 *          0: SUCCESS
 *         -1: FAIL
 */
int
main(int argc, char** argv)
{
	/* TODO parse user input
	 */
	int port = 1251;

	AyeLog::log_verbosity = 3; // debug log

	AyeLog::logf(LOG_DEBUG, "creating DataHandler ...");
	/* The data handler manages information and translates commands
	 * appropriately:
	 */
	data_handler = new DataHandler();

	/* The network and game use the data_handler to communicate with each other
	 * and let it handle the commands:
	 */
	try {
		AyeLog::logf(LOG_DEBUG, "creating socket on port %d", port);
		network = new Network(data_handler, port);
	} catch(Exception* e) {
		AyeLog::logf(LOG_ERROR, "%s", e->str());
		delete data_handler;
		return -1;
	}
	game = new Game(data_handler);

	/* TODO deprecated
	 */
	printf("\nType `help' to see a list of available commands.\n\n");

	for(bool term_signal = false; !term_signal; ) {
		try {
			network->poll();
			game->poll();
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

