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
 * @return      The name of the window that shall be focused next.
 */
WindowName
Map::process(int input)
{
	// TODO
	return IDENTITY;
}

/**
 * @override
 * This method defines what happens if this window gains focus.
 */
void
Map::focus(void)
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
Map::unfocus(void)
{
	// TODO
	return true;
}

