#include "ncurses_wm.h"

/**
 * Constructor.
 */
NCursesWM::NCursesWM(void)
{
	// TODO create windows
}

/**
 * Destructor.
 */
NCursesWM::~NCursesWM(void)
{
	for(size_t i = 0; i < windows.size(); i++) {
		delete windows[i];
	}
}


/* PUBLIC METHODS */


/**
 * This method processes a user input (button) by sending it to the right window
 * to react accordingly.
 * @param input The key pressed by the user.
 */
void
NCursesWM::process(char input)
{
	// TODO
}

