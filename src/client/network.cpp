/*
 * EYVA - client side network handler
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
 * @param pipe The GUI's "postbox". It's required to communicate to the GUI.
 * @param ip   The IP of the server to connect to.
 * @param port The TCP port of the server to connect to.
 */
Network::Network(Pipe* pipe, char const* ip, int port)
{
	this->pipe = pipe;
	for(int i = 0; i < BUFFER_SIZE; i++)
		buffer[i] = 0;

	// create socket:
	sockc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sockc < 0)
		throw new Exception("creating socket failed");
	
	// set socket non-blocking, as we also need to poll the UI:
	fcntl(sockc, F_SETFL, O_NONBLOCK);

	// prepare server information for use with connect():
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;            // use IPv4
	server_addr.sin_addr.s_addr = inet_addr(ip); // connect to given IP
	server_addr.sin_port = htons(port);          // ... and given port

	// connect to server according to the struct above:
	logf(LOG_DEBUG, "connecting to %s:%d ...", ip, port);
	if(::connect(sockc, (sockaddr*)&server_addr, sizeof(server_addr)) < 0)
		throw new Exception("connect() failed: %s", strerror(errno));

	logf(LOG_NORMAL, "connection established to %s:%d", ip, port);
}

Network::~Network(void)
{
	// zero byte message to close the connection, then close socket:
	::send(sockc, NULL, 0, MSG_NOSIGNAL);
	close(sockc);
}


/* PUBLIC METHODS */


/**
 * Checks incoming network data and forwards them to the UI.
 * @return False if the connection has been closed by the server.
 */
bool
Network::poll(void)
{
	// read data to buffer:
	int received = read(sockc, buffer, BUFFER_SIZE);


	// if zero bytes where received, the connection has been closed:
	if(received == 0)
		return false;
	
	// if a positive number of bytes have been received, handle them:
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

