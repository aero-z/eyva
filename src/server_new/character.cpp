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

#include "character.h"

/**
 * Constructor.
 * @param session_id   The session ID and socket needed to communicate with the
 *                     network handler.
 * @param character_id The character's unique ID in the game.
 */
Character::Character(int session_id, int character_id)
{
	this->session_id = session_id;
	this->character_id = character_id;

	// TODO read data from character save file
}

/**
 * Destructor.
 */
Character::~Character(void)
{
	// TODO save to file
}


/* PUBLIC METHODS */


/**
 * @return The character's session ID (also socket).
 */
int
Character::getSessionID(void)
{
	return session_id;
}

/**
 * @return The character's ID.
 */
int
Character::getCharacterID(void)
{
	return character_id;
}

/**
 * @return The character's level.
 */
unsigned int
Character::getLevel(void)
{
	return level;
}

/**
 * @return The character's name.
 */
char const*
Character::getName(void)
{
	return name;
}

