/*
 * `eyva' (server) handles one connection
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

#include "session.h"

using namespace AyeLog;
using namespace AyeString;

/**
 * @param id            The session ID (= socket file descriptor for this
 *                      connection).
 * @param pipe_game      A way to communicate to the game.
 * @param pipe_network   A way to communicate to the network object.
 * @param savefile_users Handles the file containing a list of registred users.
 */
Session::Session(int id, Pipe* pipe_game, Pipe* pipe_game,
		Savefile* savefile_users)
{
	this->id = id;
	this->pipe_game = pipe;
	this->pipe_network = pipe_network;
	this->savefile_users = savefile_users;
	authenticated = false;
	synchronized = false;
}

Session::~Session(void)
{
	// TODO log out from game
}


/* PUBLIC METHODS */


/**
 * This method handles a message received by the client.
 * @param msg     The received message.
 * @param msg_len The received message's length.
 */
void
Session::process(char const* msg, size_t msg_len)
{
	/* TODO
	 * This is temporary, until we've got an admin client:
	 */
	if(msg_len == 3 && msg[0] == ':' && msg[1] == 'q' && msg[2] == 10) {
		logf(LOG_DEBUG, ":q");
		char response[] = {0x00, 0x00, 0x00, 0x00};
		pipe->push(response);
		return;
	}

	/* Check message length:
	 */
	if(msg_len < 4 || msglen(msg) != msg_len) {
		logf(LOG_DEBUG, "[52 ERROR_MESSAGE_LEN] (%u instead of %u)",
				msg_len, msg_len >= 4 ? msglen(msg) : 0);
		char response[] = {session_id, 0x52, 0x00, 0x00};
		pipe->push(response);
		return;
	}

	/* This is the part where the messages are checked and processed:
	 */
	switch(msg[1]) {
		case 0x11:
			handle_CONNECT(msg);
			break;
		case 0x15:
			handle_DISCONNECT(msg);
			break;
		case 0x16:
			authenticated ?
					handle_REQUEST_CHARACTER_LIST(msg) :
					handle_ERROR_AUTHENTICATION();
			break;
		default:
			authenticated ?
					game->process(msg) :
					handle_ERROR_AUTHENTICATION();
			break;
	}
}

/**
 * @return The IP of this session's client.
 */
char const*
Session::getIP(void)
{
	return ip;
}

/**
 * @return The session ID (and also socket file descriptor).
 */
int
Session::getSessionID(void)
{
	return session_id;
}


/* PRIVATE METHODS */


/* This method handles the [11 CONNECT] message.
 * That's the first message to be received by the client. It contains the
 * client's software version on bytes 10-12, plus the username on bytes 13+
 * (zero terminated).
 * @param msg The message received from the client.
 */
void
Session::handle_CONNECT(char const* msg)
{
	logf(LOG_DEBUG, "[11 CONNECT]");
	bool valid = true;

	/* Check client software version:
	 */
	valid = valid && (msg[10] == VERSION_MAJOR_RELEASE);
	valid = valid && (msg[11] == VERSION_MINOR_RELEASE);
	valid = valid && (msg[12] == VERSION_PATCH);
	if(!valid) { // [51 ERROR_CLIENT_COMPATIBILITY]
		logf(LOG_DEBUG, "[51 ERROR_CLIENT_COMPATIBILITY]");
		char response[] = {session_id, 0x51, 0x03, 0x00,
				VERSION_MAJOR_RELEASE, VERSION_MINOR_RELEASE,
				VERSION_PATCH};
		pipe->push(response);
		return;
	}

	/* Check login credentials:
	 */
	try {
		user = new User(msg+13, user_savefile);
	} catch(Exception* e) {
		logf(LOG_WARNING, "%s", e->str());
		valid = false;
	}
	// TODO check password
	if(!valid) { // [50 ERROR_AUTHENTICATION]
		logf(LOG_DEBUG, "[51 ERROR_AUTHENTICATION]");
		char response[] = {session_id, 0x50, 0x00, 0x00};
		pipe->push(response);
		return;
	}

	// [12 ACCEPT_CONNECTION]
	logf(LOG_DEBUG, "[12 ACCEPT_CONNECTION]: %s", msg+13);
	authenticated = true;
	char response[] = {session_id, 0x12,0x05,0x00,'d','a','d','a','\n'};
	//TODO message of the day
	pipe->push(response);
}

/* This method handles the [15 DISCONNECT] message.
 * Its purpose is to disconnect the client. It's the `eyva' variant of the
 * zero-byte message to close a connection.
 * NOTE: This method actually doesn't do anything, but instead alerts the
 *       network handler to destroy this object (so the session handler's
 *       destructor will do the necessary stuff).
 * @param msg The message received from the client.
 */
void
Session::handle_DISCONNECT(char const* msg)
{
	logf(LOG_DEBUG, "[15 DISCONNECT]");
	char response[] = {session_id, 0x01, 0x00, 0x00};
	pipe->push(response);
}

/* This method handles the [16 REQUEST_CHARACTER_LIST] message.
 * It's a request for all characters belonging to a user. First check if the
 * client is correctly logged in before answering on that one:
 * @param msg The message received from the client.
 */
void
Session::handle_REQUEST_CHARACTER_LIST(char const* msg)
{
	logf(LOG_DEBUG, "[16 REQUEST_CHARACTER_LIST]");
	std::vector<int> characters;
	user_savefile->getCharacters(&characters, session_id);
	char response[characters.size()+4];

	// [17 CHARACTER_LIST]
	response[0] = session_id;
	response[1] = 0x17;
	response[2] = characters.size();
	response[3] = 0;
	for(size_t i = 0; i < characters.size(); i++)
		response[i+4] = characters[i];
	pipe->push(response);
}

/**
 * This method sends the [50 ERROR_AUTHENTICATION] message to the client.
 */
void
Session::handle_ERROR_AUTHENTICATION(void)
{
	char response[] = {session_id, 0x50, 0x00, 0x00};
	pipe->push(response);
}

