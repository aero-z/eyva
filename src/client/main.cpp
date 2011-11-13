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
	pipe = new Pipe();
	ui = new UI(pipe, game);
	network = new Network(game, ui, pipe);

	/* Loop: Check for activitiy on the network layer, then for activity on
	 * userspace level.
	 */
	for(bool term_signal = false; !term_signal; ) {
		network->poll();
		ui->poll(1.0);
		// TODO quit loop if needed
	}

	delete game;
	delete ui;
	delete network;
	delete pipe;
	return 0;
}

