#include "playground.h"

/**
 * Constructor.
 */
Playground::Playground(Game* game) :
		Window(0, 1, 80, 20)
{
	this->game = game;

	// TODO fill map with game data
}

/**
 * Destructor.
 */
Playground::~Playground(void)
{
	// VOID
}


/* PUBLIC METHODS */


/**
 * This method handles the user input for the panel.
 * @param input The user's input key.
 * @return      The name of the window that shall be focused next.
 */
WindowName
Playground::process(int input)
{
	switch(input) {
		case 10: // ENTER
			return BOTTOM_PANEL;
		case ':':
			return BOTTOM_PANEL_COMMAND;
		default:
			return IDENTITY;
	}
}

/**
 * This method defines what happens if this window gains focus.
 */
void
Playground::focus(void)
{
	curs_set(0);
}

/**
 * This method defines what happens if this window loses focus.
 * @return False if this window shall be destroyed, otherwise true.
 */
bool
Playground::unfocus(void)
{
	return true;
}

