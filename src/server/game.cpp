/*
 * `eyva' (server) - Game manager and handler (implementation).
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

#include "game.h"

/**
 * Constructor.
 * @param data_handler A pointer to the data handler that is needed to
 *                     communicate with the network object.
 */
Game::Game(Pipe* pipe)
{
	this->pipe = pipe;
	character_savefile = new FileHandler("usr/characters.db");
	object_database = new FileHandler("usr/objects.db");
}

/**
 * Destructor.
 */
Game::~Game(void)
{
	character_savefile->save();
	delete character_savefile;
	delete object_database;
}


/* PUBLIC METHODS */


/**
 * This method "executes" a message.
 * @param msg The message to be executed.
 */
void
Game::process(char const* msg)
{
	switch(msg[1]) {
		case 0x42:
			handle_REQUEST_CHARACTER_INFO(msg);
			break;
		default:
			handle_ERROR_INVALID_MESSAGE(msg);
			break;
	}
}

/**
 * This method logs out a character from the game.
 * @param session_id The session ID of the user playing the character.
 */
void
Game::logout(int session_id)
{
	for(size_t i = 0; i < characters.size(); i++)
		if(characters[i]->getSessionID() == session_id) {
			characters.erase(characters.begin()+i);
		}
}


/* PRIVATE METHODS */


/**
 * This method sends a message containing information for a given character ID.
 * @param msg The message received from the client.
 */
void
Game::handle_REQUEST_CHARACTER_INFO(char const* msg)
{
	/* Get the info from the savefile:
	 */
	int id = msg[0];
	int name_len;
	char* name = new char[name_len = character_savefile->getName(NULL, id, 0)];
	if(name_len == 0) {
		/* We know the character does not exist if its name length is 0:
		 */
		char* response = new char[4];
		response[0] = id;
		response[1] = 0x53; // [53 ERROR_CHARACTER_NOT_FOUND]
		response[2] = 0;
		response[3] = 0;
		pipe->push(response);
		return;
	}
	character_savefile->getName(name, id, strlen(name));
	int tribe = character_savefile->getTribe(id);
	int level = character_savefile->getLevel(id);

	/* Assemble the response:
	 */
	int msg_body_len = strlen(name)+3;
	char* response = new char[4+msg_body_len];
	response[0] = id;
	response[1] = 0x43; // [43 CHARACTER_INFO]
	response[2] = msg_body_len % 256;
	response[3] = msg_body_len >> 8;
	response[4] = tribe;
	response[5] = level;
	for(size_t i = 0; i < strlen(name); i++)
		response[i+6] = name[i];
	pipe->push(response);
}

/**
 * This method sends a [54 ERROR_INVALID_MESSAGE] message to the client.
 * @param msg The message received from the client.
 */
void
Game::handle_ERROR_INVALID_MESSAGE(char const* msg)
{
	char response[] = {msg[0], 0x54, 0x00, 0x00};
	pipe->push(response);
}

