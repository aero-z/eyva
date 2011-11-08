#include "main.h"

/**
 * The main function.
 * @param argc The number of arguments given.
 * @param argv A list of arguments given.
 * @return     Error code:
 *              0: SUCCESS
 *             -1: FAIL
 */
int
main(int argc, char** argv)
{
	/* TODO parse user input
	 */
	int port = 1251;

	AyeLog::log_verbosity = 3; // debug log

	try {
		AyeLog::logf(LOG_DEBUG, "creating socket on port %d", port);
		network = new Network(port);
	} catch(Exception* e) {
		AyeLog::logf(LOG_ERROR, "%s", e->str());
		return -1;
	}

	/* Loop:
	 */
	for(bool term_signal = false; !term_signal; ) {
		try {
			network->poll();
		} catch(Exception* e) {
			AyeLog::logf(LOG_ERROR, "%s", e->str());
			return -1;
		}
	}

	delete network;
	return 0;
}

