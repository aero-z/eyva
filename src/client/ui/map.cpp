#include "map.h"

/**
 * Constructor.
 * @param game   The game handler that holds all informations about the game.
 * @param xpos   The X coordinate of the upper left corner of the window.
 * @param ypos   The Y coordinate of the upper left corner of the window.
 * @param width  The window's width.
 * @param height The window's height.
 */
Map::Map(Game* game, int xpos, int ypos, int width, int height) :
		Window(xpos, ypos, width, height)
{
	this->game = game;
}

/**
 * Destructor.
 */
Map::~Map(void)
{
	// VOID
}


/* PUBLIC METHODS */


/**
 * @override
 * This method processes a user input.
 * @param input The user input.
 * @return      False if the window shall lose focus on this user action,
 *              otherwise true.
 */
bool
Map::process(int input)
{
	// TODO
	return true;
}

/**
 * @override
 * This method defines what happens if this window gains focus.
 */
void
Map::focusWindow(void)
{
	curs_set(0);
}

/**
 * @override
 * This method defines what happens if this window loses focus.
 * @return False if the window shall be destroyed after losing focus, otherwise
 *         true.
 */
bool
Map::unfocusWindow(void)
{
	// TODO
	return true;
}

