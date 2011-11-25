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

// Client:
#include "pipe.h"
#include "ui/ui.h"
#include "game.h"

// Utils:
#include <utils/ayelog.h>
#include <utils/exception.h>

// Hybrid:
#include <hybrid/eyva.h>

// Network:
#include <sys/types.h>   // socket types
#include <sys/socket.h>  // sockets
#include <arpa/inet.h>   // inet (3) functions
#include <unistd.h>      // for write, read
#include <fcntl.h>       // for non-blocking socket

// Others:
#include <cerrno>
#include <cstring>

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

class
Network
{
	public:
		Network(Game* game, UI* ui, Pipe* pipe);
		~Network(void);
		void poll(void);

	private:
		bool connect(char const* ip, int port);
		void disconnect(void);
		void pollIn(void);
		void pollOut(void);

		Game* game;
		UI* ui;
		Pipe* pipe;
		int sockc;
		char buffer_in[BUFFER_SIZE];
		char buffer_out[BUFFER_SIZE];
		bool connected;
};

#endif

