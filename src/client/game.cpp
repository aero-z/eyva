#include "game.h"

/**
 * Constructor.
 */
Game::Game(void)
{
	region = new Region();
}

/**
 * Destructor.
 */
Game::~Game(void)
{
	delete region;
}


/* PUBLIC METHODS */


/**
 * This method processes a network message received by the server.
 * @param msg The eyva protocol compliant message.
 */
void
Game::process(char const* msg)
{
	// TODO
}

