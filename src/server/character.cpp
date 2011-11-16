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

