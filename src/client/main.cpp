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

	game = new Game();
	network_pipe = new Pipe();
	ui = new UI(network_pipe, game);
	network = new Network(game, ui, network_pipe);

	/* Loop: Check for activitiy on the network layer, then for activity on
	 * userspace level.
	 */
	for(bool term_signal = false; !term_signal; ) {
		network->poll();
		ui->poll(1.0);
		term_signal = ui->checkTermSignal();
	}

	delete game;
	delete ui;
	AyeLog::logf(LOG_NORMAL, "shutting down eyva client ...");
	delete network;
	delete network_pipe;
	return 0;
}

