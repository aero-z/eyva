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
	this->pipe_network = new Pipe();
	this->pipe_game = pipe_game;
	this->savefile_users = new Savefile("usr/savefiles/users.db");

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
	savefile_users->save();
	delete savefile_users;
}


/* PUBLIC METHODS */


/**
 * Check for incoming data. The game class should check the pipe for the results
 * of the polling.
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
			logf(LOG_DEBUG, "data on %d ...", it->first);
			handleData(it->first);
		}
	
	// check for data to send by the session handler (somewhat ugly design ...):
	while(pipe_network->fetch(buffer, NETWORK_BUFFER_SIZE) != 0)
		send(buffer);
}


/**
 * Send a message to a client.
 * @param msg The message to be sent.
 */
void
Network::send(char const* msg)
{
	// prepare message:
	char id = msg[0];
	int msg_len = msglen(msg);
	char* prepared = new char[msg_len+1];
	memcpy(prepared, msg, msg_len);
	prepared[msg_len] = 0;  // check byte

	// send:
	logf(LOG_DEBUG, "sending %d+1 bytes to %d ...", msg_len, id);
	int sent = ::send(id, prepared, msg_len+1, MSG_NOSIGNAL); // <- no crash!
	delete[] prepared;
	if(sent <= 0) {
		logf(LOG_WARNING, "%d: connection lost", id); 
		close(id);
		sessions.erase(id);
	}
}


/* PRIVATE METHODS */


/**
 * Handle incoming connections. For each connection accepted, add a session
 * object to the sessions map.
 */
void
Network::handleConnection(void)
{
	// accept the connection (TODO handle error):
	int sock_new = accept(sockc, NULL, NULL);
	if(sock_new < 0)
		throw new Exception("accept() failed");

	// if there's space, create a new session according to the socket:
	if(sessions.size() < SESSIONS_MAX) {
		sessions.insert(std::pair<int, Session*>(sock_new,
				new Session((char)sock_new, pipe_game, pipe_network,
				savefile_users)));
		logf(LOG_NORMAL, "\e[32m%d\e[0m: new connection", sock_new);
	} else
		close(sock_new);
}

/**
 * Handle incoming data on a socket.
 * @param socket The socket which holds the data.
 */
void
Network::handleData(char socket)
{
	// get data on socket (TODO handle error):
	int received = read(socket, buffer, NETWORK_BUFFER_SIZE);
	if(received < 0)
		throw new Exception("read() failed");

	// check if the connection has been closed by peer:
	if(received == 0) {
		logf(LOG_NORMAL, "\e[33m%d\e[0m: connection closed by peer", socket);
		close(socket);
		sessions.erase(socket);
		return;
	}

	// if everything is OK, send a confirmation byte:
	char confirmation_byte = '\n';
	int sent = ::send(socket, &confirmation_byte, 1, MSG_NOSIGNAL);
	if(sent != 1) {
		logf(LOG_WARNING, "%d: connection lost", socket);
		close(socket);
		sessions.erase(socket);
		return;
	}

	sessions[socket]->process(buffer, (size_t)received);
}

