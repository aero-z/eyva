/*
 * EYVA - client side static network handler
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
using namespace AyeString;

// static:
Pipe* Network::pipe = NULL;
MessageBuffer* Network::message_buffer = NULL;
char Network::buffer[NETWORK_BUFFER_SIZE];
int Network::sockc;
bool Network::connected = false;


/* PUBLIC METHODS */


/**
 * Connect to the server.
 * @param pipe The GUI's "postbox". It's required to communicate to the GUI.
 * @param ip   The IP of the server to connect to.
 * @param port The TCP port of the server to connect to.
 */
void
Network::connect(Pipe* pipe, char const* ip, int port)
{
	Network::pipe = pipe;
	message_buffer = new MessageBuffer();
	for(int i = 0; i < NETWORK_BUFFER_SIZE; i++)
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

	connected = true;
	logf(LOG_NORMAL, "connection established to %s:%d", ip, port);
}

/**
 * Disconnect from the server.
 */
void
Network::disconnect(void)
{
	if(connected) {
		// zero byte message to close the connection, then close socket:
		::send(sockc, NULL, 0, MSG_NOSIGNAL);
		close(sockc);

		delete message_buffer;
		connected = false;
	}
}


/**
 * Checks incoming network data and forwards them to the UI.
 * @return False if the connection has been closed by the server.
 */
bool
Network::poll(void)
{
	// read data to buffer:
	int received = read(sockc, buffer, NETWORK_BUFFER_SIZE);
	if(received == 0)
		return false;
	
	// if a positive number of bytes have been received, handle them:
	if(received > 0) {
		std::vector<char*> prepared;
		message_buffer->check(&prepared, buffer, received);
		for(size_t i = 0; i < prepared.size(); i++)
			pipe->push(prepared[i]);
	}

	// as non-blocking, -1 is likely to happen, so treat it as success, too:
	return true;
}

/**
 * Send data to the server.
 * @param msg The message to be sent.
 * @return    True if successful, otherwise false.
 */
bool
Network::send(char const* msg)
{
	// prepare message:
	size_t msg_len = msglen(msg);
	char* prepared = new char[msg_len+1];
	memcpy(prepared, msg, msg_len);
	prepared[msg_len] = 0; // check byte

	// send:
	int sent = ::send(sockc, prepared, msg_len+1, MSG_NOSIGNAL);
	delete[] prepared;
	return(sent <= 0);
}

