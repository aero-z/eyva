#include "window.h"

/**
 * Constructor.
 * @param xpos   The window's upper left edge's X coordinate.
 * @param ypos   The window's upper left edge's Y coordinate.
 * @param width  The window's width.
 * @param height The window's height.
 */
Window::Window(int xpos, int ypos, int width, int height)
{
	moveWindow(xpos, ypos);
	resizeWindow(width, height);
}


/* PUBLIC METHODS */


/**
 * This method handles an input. This is the basic window class, so one may only
 * unfocus the window.
 * @param input The user input.
 */
bool
Window::process(int input)
{
	/* unfocus if ESC:
	 */
	return(input == 27);
}

/**
 * This method defines what happens if the window gains focus.
 */
void
Window::focusWindow(void)
{
	curs_set(0);
}

/**
 * This method defines what happens if the window loses focus.
 * @return False if the window shall be destroyed, otherwise true.
 */
bool
Window::unfocusWindow(void)
{
	return false;
}

/**
 * This method moves the window to a specified position.
 * @param xpos The X coordinate where the upper left corner shall be.
 * @param ypos The Y coordinate where the upper left corner shall be.
 */
void
Window::moveWindow(int xpos, int ypos)
{
	this->xpos = xpos;
	this->ypos = ypos;
}

/**
 * This method resizes the window to a specified size.
 * @param width  The window's new width.
 * @param height The window's new height.
 */
void
Window::resizeWindow(int width, int height)
{
	this->width = width;
	this->height = height;
}


/* PROTECTED METHODS */


/**
 * This method prints a character to the window area.
 * @param x     The window-relative X coordinate.
 * @param y     The window-relative Y coordinate.
 * @param c     The character to be printed.
 * @param fg    An enum indicating the foreground (text) color.
 * @param bg    An enum indicating the background color.
 */
void
Window::printch(int x, int y, char c, Color fg=BLACK, Color bg=WHITE)
{
	// TODO handle colors
	if(x >= 0 && x < width && y >= 0 && y < height)
		mvaddch(ypos+y, xpos+x, c);
}

