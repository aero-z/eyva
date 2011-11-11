#include "wm.h"

/**
 * Constructor.
 */
WM::WM(void)
{
	game = new Game();
	panel = new Panel(game, 0, 20, 80, 4);
	
	// TODO
	focus = panel;

	focus->focusWindow();
}

/**
 * Destructor.
 */
WM::~WM(void)
{
	delete panel;
	delete game;
}


/* PUBLIC METHODS */


/**
 * This method processes a user input (button) by sending it to the currently
 * focused window.
 * @param input The key pressed by the user.
 */
void
WM::process(int input)
{
	// TODO check return value to update focus
	focus->process(input);
}

