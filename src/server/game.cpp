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

#include "game.h"

/**
 * Constructor.
 * @param data_handler A pointer to the data handler that is needed to
 *                     communicate with the network object.
 */
Game::Game(Pipe* pipe)
{
	this->pipe = pipe;
	// TODO
}

/**
 * Destructor.
 */
Game::~Game(void)
{
	// VOID
}


/* PUBLIC METHODS */


/**
 * This method "executes" a message.
 * @param msg The message to be executed.
 */
void
Game::process(char const* msg)
{
	// TODO
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


