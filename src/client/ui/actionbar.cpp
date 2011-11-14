#include "actionbar.h"

/**
 * Constructor.
 * @param game The game that handles and holds all game related data.
 */
Actionbar::Actionbar(Game* game) :
		Window(0, 21, 80, 3)
{
	this->game = game;

	repaint();
}

/**
 * Destructor.
 */
Actionbar::~Actionbar(void)
{
	// VOID
}


/* PUBLIC METHODS */

/**
 * This method processes a user input. Since this is the actionbar (and thus
 * never focused), it will automatically return to the playground window.
 * @param input The user's input key.
 * @return      The name of the next window that shall be focused.
 */
WindowName
Actionbar::process(int input)
{
	return PLAYGROUND;
}

/**
 * This method defines the behaviour of the window when focused. Since this is
 * the actionbar (and thus never focused), it won't do anything.
 */
void
Actionbar::focus(void)
{
	// VOID
}

/**
 * This method defines the behaviour of the window when unfocused. Since this is
 * the actionbar (and thus never (un)focused), it won't do anything.
 * @return False if the window shall be destroyed at unfocusing, otherwise true.
 */
bool
Actionbar::unfocus(void)
{
	return true;
}

/**
 * This method repaints the window.
 */
void
Actionbar::repaint(void)
{
	setBG(11);

	refresh();
}

