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
	initColors();
	moveWindow(xpos, ypos);
	this->width = width;
	this->height = height;
}

/**
 * Destructor.
 * This destructor is marked virtual, but will still be executed (probably
 * that's a special case for destructors).
 */
Window::~Window(void)
{
	// VOID
}


/* PUBLIC METHODS */


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


/* PROTECTED METHODS */


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

	// on black background:
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);

	// on yellow background:
	init_pair(30, COLOR_BLACK, COLOR_YELLOW);
	init_pair(31, COLOR_RED, COLOR_YELLOW);
	init_pair(32, COLOR_GREEN, COLOR_YELLOW);
	init_pair(34, COLOR_BLUE, COLOR_YELLOW);
	init_pair(35, COLOR_MAGENTA, COLOR_YELLOW);
	init_pair(36, COLOR_CYAN, COLOR_YELLOW);
	init_pair(37, COLOR_WHITE, COLOR_YELLOW);

	// on white background:
	init_pair(70, COLOR_BLACK, COLOR_WHITE);
	init_pair(71, COLOR_RED, COLOR_WHITE);
	init_pair(72, COLOR_GREEN, COLOR_WHITE);
	init_pair(73, COLOR_YELLOW, COLOR_WHITE);
	init_pair(74, COLOR_BLUE, COLOR_WHITE);
	init_pair(75, COLOR_MAGENTA, COLOR_WHITE);
	init_pair(76, COLOR_CYAN, COLOR_WHITE);
}

/**
 * This method draws the background in specified color.
 * @param color The number of the color pair to be used (see above).
 *              Since only the background (with empty foreground) is drawn, the
 *              foreground color doesn't matter and the color value can
 *              therefore be set to one of the following values:
 *              -  1 BLACK
 *              - 10 RED
 *              - 20 GREEN
 *              - 30 YELLOW
 *              - 40 BLUE
 *              - 50 MAGENTA
 *              - 60 CYAN
 *              - 70 WHITE
 */
void
Window::setBG(int color)
{
	attron(COLOR_PAIR(color));
	for(int x = 0; x < width; x++)
		for(int y = 0; y < height; y++)
			mvaddch(ypos+y, xpos+x, ' ');
	attroff(COLOR_PAIR(color));
}

