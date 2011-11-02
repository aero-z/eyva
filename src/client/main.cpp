#include "main.h"

int main(int argc, char** argv) {
	/* TODO parse user input
	 */

	AyeLog::log_verbosity = 0;   // no log output

	/* The data handler manages information and translates commands
	 * appropriately:
	 */
	data_handler = new DataHandler();

	/* The network and UI use the data_handler to communicate with each
	 * other and to let it handle the commands:
	 */
	try {
		network = new Network(data_handler, "127.0.0.1", 1251);
	} catch(Exception* e) {
		AyeLog::logf(LOG_ERROR, "%s", e->str());
		cleanUp();
		return -1;
	}
	try {
		ui = new NCursesUI(data_handler);
	} catch(Exception* e) {
		AyeLog::logf(LOG_ERROR, "%s", e->str());
		delete network;
		cleanUp();
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
			term_signal = data_handler->checkTermSignal();
		} catch(Exception* e) {
			AyeLog::logf(LOG_ERROR, "%s", e->str());
			term_signal = true;
		}
	}

	delete ui;
	delete network;
	cleanUp();
}

void cleanUp(void) {
	delete data_handler;
}
