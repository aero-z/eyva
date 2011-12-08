/*
 * EYVA - server side game handler
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

#ifndef _GAME_H_
#define _GAME_H_

#include "network.h"
#include <generic/pipe.h>
#include <generic/utils/ayestring.h>

class
Game
{
	public:
		Game(int port);
		~Game(void);
		void run(void);
	
	private:
		void process();

		Pipe* pipe;
		Network* network;
		bool term_signal;
		char buffer[NETWORK_BUFFER_SIZE];
};

#endif

