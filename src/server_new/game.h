/*
 * `eyva' (server) - Game manager and handler.
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

// Server:
#include "character.h"
#include "pipe.h"

// Utils:
#include <utils/file_handler.h>

class
Game
{
	public:
		Game(Pipe* pipe);
		~Game(void);
		void process(char const* msg);
		void logout(int session_id);
	
	private:
		void handle_REQUEST_CHARACTER_INFO(char const* msg);
		void handle_ERROR_INVALID_MESSAGE(char const* msg);

		Pipe* pipe;
		std::vector<Character*> characters;
		FileHandler* character_savefile;
		FileHandler* object_database;
};

#endif

