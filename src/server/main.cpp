/*
 * EYVA - server side main function
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
 * @param argc Number of arguments given at program start.
 * @param argv Array of arguments.
 * @return     0 if success, otherwise -1.
 */
int
main(int argc, char** argv)
{
	// TODO parse user input
	int port = 1251;

	AyeLog::log_verbosity = 3; // debug log

	try {
		game = new Game(port);
		game->run();
		delete game;
		return 0;
	} catch(Exception* e) {
		AyeLog::logf(LOG_ERROR, "%s", e->str());
		return -1;
	}
}

