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

#ifndef _NETWORK_H_
#define _NETWORK_H_

// Server side headers:
#include "session.h"
#include "game.h"
#include "pipe.h"

// Non-specific headers:
#include <hybrid/eyva.h> 

// Utilities:
#include <utils/ayelog.h>
#include <utils/exception.h>
#include <utils/ayestring.h>
#include <utils/file_handler.h>

// Network headers:
#include <sys/types.h>  // socket types
#include <sys/socket.h> // sockets
#include <arpa/inet.h>  // inet (3) functions
#include <unistd.h>     // for write, read
#include <cerrno>       // for the "errno" macro

// Others:
#include <cstring>
#include <vector>
#include <map>
#include <utility>

/* Mac OS X does not know the MSG_NOSIGNAL flag; therefore we "link"
 * MSG_NOSIGNAL to SO_NOSIGPIPE.
 * (If there's an error with sending data, the application crashes at send(),
 * rather than returning -1. That's the default behaviour (FSM knows why), so to
 * avoid that, the flag is required.)
 *
 * TODO see if Linux would also get along with SO_NOSIGPIPE
 */
#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL SO_NOSIGPIPE
#endif

/* Number of sessions that this server can handle:
 */ 
#define SESSIONS_MAX 10

/* Number of connection requests this server can keep in a queue:
 */
#define QUEUE_SIZE 3

class
Network
{
	public:
		Network(int port);
		~Network(void);
		void poll(void);
		bool checkTermSignal(void);

	private:
		void pollIn(void);
		void handleConnection(void);
		void handleData(int id);
		void pollOut(void);

		Game* game;
		Pipe* pipe;
		FileHandler* user_savefile;
		std::map<int, Session*> sessions;
		std::map<int, Session*>::iterator it; // iterator for the sessions map
		int sockc;                            // connection socket
		char buffer_in[BUFFER_SIZE];
		char buffer_out[BUFFER_SIZE];
		bool term_signal;
};

#endif

