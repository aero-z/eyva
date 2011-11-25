/*
 * `eyva'
 * Copyright (C) 2011 ayekat (martin.weber@epfl.ch)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

	// on white background:
	init_pair(1, COLOR_RED, COLOR_WHITE);
	init_pair(2, COLOR_GREEN, COLOR_WHITE);
	init_pair(3, COLOR_YELLOW, COLOR_WHITE);
	init_pair(4, COLOR_BLUE, COLOR_WHITE);
	init_pair(5, COLOR_MAGENTA, COLOR_WHITE);
	init_pair(6, COLOR_CYAN, COLOR_WHITE);
	init_pair(7, COLOR_BLACK, COLOR_WHITE);

	// others:
	init_pair(10, COLOR_WHITE, COLOR_BLUE); // e.g. prompt
	init_pair(11, COLOR_BLACK, COLOR_BLACK); // e.g. actionbar

	// playground-specific:
	init_pair(20, COLOR_CYAN, COLOR_BLUE);  // e.g. water
}

/**
 * This method draws the background with specified color pair.
 * @param color The number of the color pair to be used (see above).
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

