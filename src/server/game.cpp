#include "game.h"

/**
 * Constructor.
 * @param data_handler A pointer to the data handler that is needed to
 *                     communicate with the network object.
 */
Game::Game(Pipe* pipe)
{
	this->pipe = pipe;
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


