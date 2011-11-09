#include "main.h"

/**
 * The main function.
 * The program loop is running in here.
 * @param argc Number of arguments passed on program invoke.
 * @param argv String array containing the arguments.
 */
int
main(int argc, char** argv)
{
	AyeLog::log_verbosity = 3;   // debug log output

	/* The postmaster object is used by the network handler and the UI to
	 * communicate with each other:
	 */
	pm = new Postmaster();
	network = new Network(pm);
	ui = new NCursesUI(pm);

	/* Loop: Check for activitiy on the network layer, then for activity on
	 * userspace level.
	 */
	for(bool term_signal = false; !term_signal; ) {
		network->poll();
		ui->poll(0.1);
		// TODO quit loop if needed
	}

	delete ui;
	delete network;
	delete pm;
	return 0;
}

