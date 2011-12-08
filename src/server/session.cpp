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
 * @param id             The session ID (= socket file descriptor for this
 *                       connection).
 * @param pipe_game      A way to communicate to the game.
 * @param pipe_network   A way to communicate to the network object.
 * @param savefile_users Handles the file containing a list of registred users.
 */
Session::Session(char id, Pipe* pipe_game, Pipe* pipe_network,
		Savefile* savefile_users)
{
	this->id = id;
	this->pipe_game = pipe_game;
	this->pipe_network = pipe_network;
	this->savefile_users = savefile_users;
	authenticated = false;
	synchronized = false;
	message_buffer = new MessageBuffer();
}

Session::~Session(void)
{
	// TODO log out from game
}


/* PUBLIC METHODS */


/**
 * Handle data received over the network.
 * @param msg     Received data.
 * @param msg_len Size of the received data.
 */
void
Session::process(char const* msg, size_t msg_len)
{
	for(size_t i = 0; i < msg_len; i++)
		printf("[%d]", msg[i]);
	printf("\n");

	// TODO this is temporary:
	if(msg_len == 3 && msg[0] == ':' && msg[1] == 'q' && msg[2] == 10) {
		logf(LOG_DEBUG, ":q");
		char response[] = {0x00, 0x00, 0x00, 0x00};
		pipe_game->push(response);
		return;
	}

	// check message validity and process complete messages:
	std::vector<char*> messages;
	message_buffer->check(&messages, msg, msg_len);
	for(size_t i = 0; i < messages.size(); i++) {
		switch(messages[i][1]) {
			case 0x01:
				handle_SOFTWARE_VERSION(messages[i]);
				break;
			case 0x05:
				handle_USER_LOGIN(messages[i]);
				break;
			case 0x08:
				handle_DISAUTHENTICATE();
				break;
			default:
				if(!synchronized)
					send_REQUEST_SOFTWARE_VERSION();
				else if(!authenticated)
					send_REQUEST_USER_LOGIN();
				else {
					messages[i][0] = id;
					pipe_game->push(messages[i]);
				}
				break;
		}
	}
}


/* PRIVATE METHODS */


/**
 * Check if the client has got the right software version.
 * @param msg The message received from the client.
 */
void
Session::handle_SOFTWARE_VERSION(char const* msg)
{
	logf(LOG_DEBUG, "[01 SOFTWARE_VERSION]");

	// if valid:
	if(msg[4] == VERSION_MAJOR_RELEASE && msg[5] == VERSION_MINOR_RELEASE
			&& msg[6] == VERSION_MAJOR_PATCH) {
		logf(LOG_DEBUG, "[02 SYNCHRONIZED]");
		synchronized = true;
		char response[] = {id, 0x02, 0x00, 0x00};
		pipe_network->push(response);
	}

	// if invalid:
	else {
		logf(LOG_DEBUG, "[03 UNSYNCHRONIZED]");
		synchronized = false;
		char response[] = {id, 0x03, 0x03, 0x00, VERSION_MAJOR_RELEASE,
				VERSION_MINOR_RELEASE, VERSION_MAJOR_PATCH};
		pipe_network->push(response);
	}
}

/**
 * Check user login data.
 * @param msg The message received from the client.
 * // TODO password check
 * // TODO message of the day
 */
void
Session::handle_USER_LOGIN(char const* msg)
{
	// if valid:
	try {
		logf(LOG_DEBUG, "[06 AUTHENTICATED]");
		authenticated = true;
		user = new User(msg+4, savefile_users);
		char response[] = {id, 0x06, 0x00, 0x00,
			'W','e','l','c','o','m','e',' ','t','o',' ','E','Y','V','A',0};
		pipe_network->push(response);
	}
	
	// if invalid:
	catch(Exception* e) {
		logf(LOG_DEBUG, "[07 DISAUTHENTICATED] (user not found: %s)", msg+4);
		authenticated = false;
		char response[] = {id, 0x07, 0x01, 0x00, 0x00};
		pipe_network->push(response);
	}

}

/**
 * Handle disauthentication message by client.
 */
void
Session::handle_DISAUTHENTICATE(void)
{
	authenticated = false;
	synchronized = false;
	logf(LOG_DEBUG, "[08 DISAUTHENTICATE]");
}

/**
 * Send a synchronization request.
 */
void
Session::send_REQUEST_SOFTWARE_VERSION(void)
{
	char response[] = {id, 0x00, 0x00, 0x00};
	logf(LOG_DEBUG, "[00 REQUEST_SOFTWARE_VERSION]");
	pipe_network->push(response);
}

/**
 * Send an authentication request.
 */
void
Session::send_REQUEST_USER_LOGIN(void)
{
	char response[] = {id, 0x04, 0x00, 0x00};
	logf(LOG_DEBUG, "[04 REQUEST_USER_LOGIN]");
	pipe_network->push(response);
}

