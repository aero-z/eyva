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

