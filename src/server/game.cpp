/*
 * `eyva' (server) - Game manager and handler (implementation).
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

#include "game.h"

using namespace AyeLog;
using namespace AyeString;

/**
 * @param port The port where the game shall run on.
 */
Game::Game(int port)
{
	logf(LOG_NORMAL, "setting up new game ...");
	pipe = new Pipe();
	network = new Network(pipe, port);
	term_signal = false;
}

Game::~Game(void)
{
	delete network;
}


/* PUBLIC METHODS */


/**
 * Game loop.
 */
void
Game::run(void)
{
	while(!term_signal) {
		network->poll();
		process();
	}
}


/* PRIVATE METHODS */


void
Game::process(void)
{
	while(pipe->fetch(buffer, NETWORK_BUFFER_SIZE)) {
		if(buffer[0] == 0)
			term_signal = true;
	}
}

