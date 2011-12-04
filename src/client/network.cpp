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

#include "network.h"

using namespace AyeLog;

/**
 * Constructor.
 * @param pipe The GUI's "postbox". It's required to communicate to the GUI.
 */
Network::Network(Pipe* pipe)
{
	this->pipe = pipe;
	connected = false;
	for(int i = 0; i < BUFFER_SIZE; i++)
		buffer[i] = 0;
}

/**
 * Destructor.
 */
Network::~Network(void)
{
	disconnect();
}


/* PUBLIC METHODS */


/**
 * This method connects the client to a server.
 * @param ip The server's IP address.
 * @param port The port on which the server is running on.
 */
bool
Network::connect(char const* ip, int port)
{
	/* Create socket:
	 * AF_INET:     domain (ARPA, IPv4)
	 * SOCK_STREAM: type (stream socket)
	 * IPPROTO_TCP: protocol (TCP)
	 */
	logf(LOG_DEBUG, "creating socket ...");
	sockc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sockc < 0) {
		logf(LOG_ERROR, "creating socket failed");
		return false;
	}
	
	/* The socket shall just be polled, so set it to non-blocking mode, which
	 * allows to go on if there's no data on the socket (remember, there's also
	 * a UI I/O going on):
	 */
	fcntl(sockc, F_SETFL, O_NONBLOCK);

	/* Prepare the server information for use with connect().
	 */
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;            // use IPv4
	server_addr.sin_addr.s_addr = inet_addr(ip); // connect to given IP
	server_addr.sin_port = htons(port);          // ... and given port

	/* Connect to the server according to the information contained by the
	 * struct that was just defined:
	 */
	logf(LOG_DEBUG, "connecting to %s:%d ...", ip, port);
	if(::connect(sockc, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		logf(LOG_ERROR, "connect() failed: %s", strerror(errno));
		return false;
	}

	logf(LOG_NORMAL, "connection established to %s:%d", ip, port);
	return(connected = true);
}

/**
 * This method closes the connection to the server.
 */
void
Network::disconnect(void)
{
	if(!connected)
		return;
	
	/* Send a zero-byte message, which will close the connection.
	 */
	::send(sockc, NULL, 0, MSG_NOSIGNAL);

	/* Close the socket:
	 */
	close(sockc);
	connected = false;
}

/**
 * This method checks incoming network data and forwards them to the UI.
 */
void
Network::poll(void)
{
	if(!connected)
		return;
	
	/* Read data to buffer:
	 */
	int received = read(sockc, buffer, BUFFER_SIZE);

	/* If the number of bytes received is equal to zero, the connection has been
	 * closed by the server:
	 */
	if(received == 0)
		disconnect();
	
	/* read() should return the number of bytes received. If there was an error,
	 * -1 is returned.
	 * Since the socket is in non-blocking mode, this is likely to happen, so
	 * just ignore it.
	 * Process the received bytes if the number is positive:
	 */
	if(received > 0) {
		// TODO received -> package handler -> gui
	}
}

/**
 * This method sends data to the server.
 * @param msg The message to be sent.
 */
void
Network::send(char const* msg)
{
	// TODO msg -> package handler -> send

	//int sent = ::send(sockc, msg, msglen(msg), MSG_NOSIGNAL);

	/* send() should return the number of bytes sent. If the number is
	 * negative or equal to zero, there must have been an error, so close
	 * the connection:
	 */
	//if(sent <= 0)
		//disconnect();
}

