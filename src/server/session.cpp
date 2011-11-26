/*
 * `eyva' (server) handles one connection
 * Copyright (C) 2011  ayekat (martin.weber@epfl.ch)
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

/**
 * Constructor.
 * @param id            The session ID (= socket file descriptor for this
 *                      connection).
 * @param ip            The client's IP address.
 * @param pipe          A pointer to where answer messages shall be stored to.
 * @param game          The game that holds and handles all game data.
 * @param user_savefile Handles the file containing the list of registred users.
 */
Session::Session(int session_id, char const* ip, Pipe* pipe, Game* game,
		FileHandler* user_savefile)
{
	this->pipe = pipe;
	this->session_id = session_id;
	this->game = game;
	this->user_savefile = user_savefile;
	authenticated = false;

	this->ip = new char[strlen(ip)+1]; // +1 for \0
	strcpy(this->ip, ip);
}

/**
 * Destructor.
 */
Session::~Session(void)
{
	/* In case the user is still logged in, log out:
	 */
	game->logout(session_id);

	/* In case the user is still connected, disconnect:
	 */
	if(authenticated)
		delete user;
	authenticated = false;

	/* Clean up:
	 */
	delete[] ip;
}


/* PUBLIC METHODS */


/**
 * This method handles a message received by the client.
 * @param message     The received message.
 * @param message_len The received message's length.
 */
void
Session::process(char const* message, size_t message_len)
{
	/* TODO
	 * This is temporary, until we've got an admin client:
	 */
	if(message_len == 3 && message[0] == ':' && message[1] == 'q'
			&& message[2] == 10) {
		logf(LOG_DEBUG, ":q");
		char response[] = {0x00, 0x00, 0x00, 0x00};
		pipe->push(response);
		return;
	}

	/* Check message length:
	 */
	if(message_len < 4 || msglen(message) != message_len) {
		logf(LOG_DEBUG, "[52 ERROR_MESSAGE_LEN] (%u instead of %u)",
				message_len, message_len >= 4 ? msglen(message) : 0);
		char response[] = {session_id, 0x52, 0x00, 0x00};
		pipe->push(response);
		return;
	}

	/* This is the part where the messages are checked and processed. It's quite
	 * a long piece of code, maybe we can move this out to an external file:
	 */
	switch(message[1]) {
		/* This is the first message to be received by the client. It contains
		 * the client's software version on bytes 10-12, plus the username to
		 * log in on bytes 13+ (zero terminated).
		 */
		case 0x11: {
			logf(LOG_DEBUG, "[11 CONNECT]");
			bool valid = true;

			/* Check client software version:
			 */
			valid = valid && (message[10] == VERSION_MAJOR_RELEASE);
			valid = valid && (message[11] == VERSION_MINOR_RELEASE);
			valid = valid && (message[12] == VERSION_PATCH);
			if(!valid) { // [51 ERROR_CLIENT_COMPATIBILITY]
				logf(LOG_DEBUG, "[51 ERROR_CLIENT_COMPATIBILITY]");
				char response[] = {session_id, 0x51, 0x03, 0x00,
						VERSION_MAJOR_RELEASE, VERSION_MINOR_RELEASE,
						VERSION_PATCH};
				pipe->push(response);
				break;
			}

			/* Check login credentials:
			 */
			try {
				for(size_t i = 0; i < strlen(message+13); i++)
					printf("[%c] ", message[13+i]);
				printf("\n");
				user = new User(message+13, user_savefile);
			} catch(Exception* e) {
				logf(LOG_WARNING, "%s", e->str());
				valid = false;
			}
			// TODO password
			if(!valid) { // [50 ERROR_AUTHENTICATION]
				logf(LOG_DEBUG, "[51 ERROR_AUTHENTICATION]");
				char response[] = {session_id, 0x50, 0x00, 0x00};
				pipe->push(response);
				break;
			}

			// [12 ACCEPT_CONNECTION]
			logf(LOG_DEBUG, "successfully logged in: %s", message+13);
			/* If login was successful, send a response [12 ACCEPT_CONNECTION].
			 * TODO message of the day
			 */
			authenticated = true;
			char response[] = {session_id, 0x12,0x05,0x00,'d','a','d','a','\n'};
			pipe->push(response);
			break;
		}

		/* This is the message received by the client to disconnect. There won't
		 * be done anything here, but instead the destructor will handle
		 * everything. Thus the network handler is alerted to destroy this
		 * session.
		 * This is the `eyva' variant to the zero-byte message to close a
		 * connection:
		 */
		case 0x15: {
			logf(LOG_DEBUG, "[15 DISCONNECT]");
			char response[] = {session_id, 0x01, 0x00, 0x00};
			pipe->push(response);
			break;
		}

		/* This is a request for all characters belonging to a user. First check
		 * if the client is correctly logged in before answering on that one:
		 */
		case 0x16: {
			logf(LOG_DEBUG, "[16 REQUEST_CHARACTER_LIST]");
			if(!authenticated) { // [50 ERROR_AUTHENTICATION]
				char response[] = {session_id, 0x50, 0x00, 0x00};
				pipe->push(response);
				break;
			}
			// TODO create message with character list
			break;
		}

		default:
			game->process(message);
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

