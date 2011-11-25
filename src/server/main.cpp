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
		AyeLog::logf(LOG_NORMAL, "creating socket on port %d ...", port);
		network = new Network(port);
	} catch(Exception* e) {
		AyeLog::logf(LOG_ERROR, "%s", e->str());
		return -1;
	}
	AyeLog::logf(LOG_NORMAL, "running");

	/* Loop:
	 */
	for(bool term_signal = false; !term_signal; ) {
		try {
			network->poll();
			term_signal = network->checkTermSignal();
		} catch(Exception* e) {
			AyeLog::logf(LOG_ERROR, "%s", e->str());
			return -1;
		}
	}

	delete network;
	return 0;
}

