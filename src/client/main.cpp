/*
 * `eyva'
 * Copyright (C) 2011 ayekat (martin.weber@epfl.ch)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

