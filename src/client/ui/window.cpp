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
	initColors();
}


/* PUBLIC METHODS */


/**
 * This method handles an input. This is the basic window class, so one may only
 * unfocus the window back to the main menu by pressing ESC.
 * @param input The user's input key.
 * @return      The name of the window that shall be focused next.
 */
WindowName
Window::process(int input)
{
	/* unfocus if ESC:
	 */
	return input == 27 ? MENU : IDENTITY;
}

/**
 * This method defines what happens if the window gains focus.
 */
void
Window::focus(void)
{
	curs_set(0);
}

/**
 * This method defines what happens if the window loses focus.
 * @return False if the window shall be destroyed, otherwise true.
 */
bool
Window::unfocus(void)
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
 * @param color The color pair defined in color.h.
 */
void
Window::printch(int x, int y, char c, int color)
{
	attron(COLOR_PAIR(color));
	if(x >= 0 && x < width && y >= 0 && y < height)
		mvaddch(ypos+y, xpos+x, c);
}

/**
 * This method defines all the color pairs we need:
 */
void
Window::initColors(void)
{
	/* Check for colors and activate if available:
	 */
	if(!has_colors())
		throw new Exception("colors not supported");
	start_color();

	/* This is to enable transparency on some terminals. We don't need that, but
	 * some terminals need it to display colors correctly:
	 */
	use_default_colors();

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);

	init_pair(30, COLOR_BLACK, COLOR_YELLOW);
	init_pair(31, COLOR_RED, COLOR_YELLOW);
	init_pair(32, COLOR_GREEN, COLOR_YELLOW);
	init_pair(34, COLOR_BLUE, COLOR_YELLOW);
	init_pair(35, COLOR_MAGENTA, COLOR_YELLOW);
	init_pair(36, COLOR_CYAN, COLOR_YELLOW);
	init_pair(37, COLOR_WHITE, COLOR_YELLOW);
}

