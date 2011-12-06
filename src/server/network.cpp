/*
 * `eyva' (server) network handler
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

/**
 * @param pipe The pipe to write messages to (alert the controlling game class).
 * @param port The TCP port to listen to.
 */
Network::Network(Pipe* pipe_game, int port)
{
	pipe_network = new Pipe();
	this->pipe_game = pipe_game;
	user_savefile = new Savefile("usr/users.db");

	// create socket and make it reusable:
	sockc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sockc < 0)
		throw new Exception("socket() failed");
	int option = 1; // TODO find out what this does
	setsockopt(sockc, SOL_SOCKET, SO_REUSEADDR, (char*)&option, sizeof(option));

	// prepare server side information:
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));    // fill with zero, then:
	server_addr.sin_family = AF_INET;                // - use IPv4
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // - allow all connections
	server_addr.sin_port = htons(port);              // - port to listen to

	// try to bind the information defined above to the socket:
	if(bind(sockc, (sockaddr *)&server_addr, sizeof(server_addr)) < 0)
		throw new Exception("bind() failed: %s", strerror(errno));

	// listen:
	if(listen(sockc, QUEUE_SIZE) < 0)
		throw new Exception("listen() failed: %s", strerror(errno));

	logf(LOG_NORMAL, "Listening on port %d ...", port);
}

Network::~Network(void)
{
	logf(LOG_NORMAL, "received shutdown signal, closing sockets ...");

	// close sockets and sessions:
	close(sockc);
	for(it = sessions.begin(); it != sessions.end(); it++)
		close(it->first);
	sessions.clear();
	delete pipe_network;

	// save user data:
	user_savefile->save();
	delete user_savefile;
}


/* PUBLIC METHODS */


/**
 * This method checks for incoming data. The game class should check the pipe
 * for the results of the polling.
 */
void
Network::poll(void)
{
	// set up socket set:
	fd_set socket_set;
	FD_ZERO(&socket_set);

	// add sockets to the set:
	FD_SET(sockc, &socket_set);
	for(it = sessions.begin(); it != sessions.end(); it++)
		FD_SET(it->first, &socket_set);

	// check sockets for activity (TODO make non-blocking and thus ignore -1):
	int selected = select(FD_SETSIZE, &socket_set, NULL, NULL, NULL);
	if(selected < 0)
		throw new Exception("select() failed");

	// in case of new connection ...
	if(FD_ISSET(sockc, &socket_set)) {
		logf(LOG_DEBUG, "incoming connection ...");
		handleConnection();
	}

	// in case of incoming data ...
	for(it = sessions.begin(); it != sessions.end(); it++)
		if(FD_ISSET(it->first, &socket_set)) {
			logf(LOG_DEBUG, "data on socket %d ...", it->first);
			handleData(it->first);
		}
}


/**
 * Send a message to a client.
 * @param id  The client ID.
 * @param msg The message to be sent.
 */
bool
Network::send(int id, char const* msg)
{
	// TODO
	return false;
}


/* PRIVATE METHODS */


/**
 * This method handles incoming connections. For each connection accepted, it
 * creates a Client object and stores it to the std::vector.
 */
void
Network::handleConnection(void)
{
	// this will hold client information:
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);

	// accept the connection (TODO handle error):
	int sock_new = accept(sockc, (sockaddr*)&client_addr, &client_addr_len);
	if(sock_new < 0)
		throw new Exception("accept() failed");

	// if there's space, create a new session according to the socket:
	if(sessions.size() < SESSIONS_MAX) {
		sessions.insert(std::pair<int, Session*>(sock_new,
				new Session(sock_new, inet_ntoa(client_addr.sin_addr), pipe,
				game, user_savefile)));
		logf(LOG_NORMAL, "> \e[32m%s\e[0m: new connection on socket %d",
				sessions[sock_new]->getIP(), sock_new);
	} else {
		close(sock_new);
	}
}

/**
 * This method handles incoming data on a socket.
 * @param socket The socket which holds the data.
 */
void
Network::handleData(int socket)
{
	/* Read data to buffer:
	 */
	int received = read(socket, buffer_in, BUFFER_SIZE);

	/* read() should return the number of bytes received. If the number is
	 * negative, there was an error, thus crash:
	 */
	logf(LOG_DEBUG, "received %d bytes", received);
	if(received < 0)
		throw new Exception("read() failed");

	/* If the number of bytes received is equal to zero, the connection has been
	 * closed by the peer:
	 */
	if(received == 0) {
		logf(LOG_NORMAL, "\e[33m%s\e[0m: connection closed by peer",
				sessions[socket]->getIP());
		close(socket);
		sessions.erase(socket);
		return;
	}

	/* Send confirmation byte for received data to make sure the client is still
	 * there:
	 */
	char confirmation_byte = 10;
	int sent = send(socket, &confirmation_byte, 1, MSG_NOSIGNAL);

	/* Check if successfully confirmation byte was successfully sent;
	 * otherwise close session:
	 */
	logf(LOG_DEBUG, "confirmation: sent %d bytes", sent);
	if(sent != 1) {
		logf(LOG_WARNING, "%s: connection lost", sessions[socket]->getIP());
		close(socket);
		sessions.erase(socket);
		return;
	}

	/* If, after all, everything is valid, let the sesssion handler process the
	 * received data:
	 */
	sessions[socket]->process(buffer_in, (size_t)received);
}

/**
 * After having handled all the incoming data, the internal server system has
 * filled the network handler's pipe with data to be sent to the clients.
 * Thus, this method will check all the messages in the pipe.
 */
void
Network::pollOut(void)
{
	while(pipe->check()) {
		size_t message_len = pipe->fetch(buffer_out);

		/* The byte zero holds the session's socket file descriptor:
		 */
		int socks = buffer_out[0];

		/* Special case: socket number is zero.
		 * This can either mean "broadcast", or an internal shutdown command:
		 */
		if(buffer_out[0] == 0) {
			/* Check for shutdown signal:
			 */
			if(buffer_out[1] == 0) {
				term_signal = true;
				return;
			}

			/* Broadcast:
			 */
			// TODO
		}

		logf(LOG_DEBUG, "sending data to %s on socket %d",
				sessions[socks]->getIP(), socks);
		 
		int sent = send(socks, buffer_out, message_len, MSG_NOSIGNAL);

		/* If there was an error sending, the client may be assumed as
		 * disconnected, and thus the session may be closed:
		 */
		if(sent <= 0) {
			logf(LOG_WARNING, "%s: connection lost", sessions[socks]->getIP());
			close(socks);
			sessions.erase(socks);
		}
	}
}

