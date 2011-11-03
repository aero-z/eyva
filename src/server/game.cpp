#include "game.h"

/**
 * Constructor.
 */
Game::Game(DataHandler* data_handler) {
	this->data_handler = data_handler;
}

/**
 * Destructor.
 */
Game::~Game(void) {
	// VOID
}


/* PUBLIC METHODS */

/**
 * This method checks if the game object was alerted by the network object, and
 * reacts accordingly.
 */
void
Game::poll(void) {
	command_len = data_handler->getGameTask(command);
	// TODO
}

