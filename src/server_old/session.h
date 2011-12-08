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

#ifndef _SESSION_H_
#define _SESSION_H_

// Game:
#include "user.h"
#include "pipe.h"
#include "game.h"

// Hybrid:
#include <hybrid/eyva.h>

// Utils:
#include <utils/ayelog.h>
#include <utils/file_handler.h>
#include <utils/exception.h>

// Others:
#include <cstring>

class
Session
{
	public:
		Session(int session_id, char const* ip, Pipe* pipe, Game* game,
				FileHandler* file_handler);
		~Session(void);
		void process(char const* msg, size_t msg_len);
		char const* getIP(void);
		int getSessionID(void);
	
	private:
		void handle_CONNECT(char const* msg);
		void handle_DISCONNECT(char const* msg);
		void handle_REQUEST_CHARACTER_LIST(char const* msg);
		void handle_ERROR_AUTHENTICATION(void);

		Pipe* pipe;
		Game* game;
		User* user;
		FileHandler* user_savefile;
		int session_id;
		char* ip;
		bool authenticated;
};

#endif

