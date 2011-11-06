#include "game.h"

/**
 * Constructor.
 * @param data_handler A pointer to the data handler that is needed to
 *                     communicate with the network object.
 */
Game::Game(DataHandler* data_handler)
{
	this->data_handler = data_handler;
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
 * This method checks if the game object was alerted by the network object, and
 * reacts accordingly.
 */
void
Game::poll(void)
{
	Client* src = NULL;
	effect_len = data_handler->getGameTask(effect, src);
	// TODO
}

