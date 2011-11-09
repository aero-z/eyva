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

