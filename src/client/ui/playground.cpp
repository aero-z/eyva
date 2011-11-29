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

#include "playground.h"

/**
 * Constructor.
 */
WinPlayground::WinPlayground(Pipe* pipe, Game* game) :
		Window(0, 1, 80, 20)
{
	this->pipe = pipe;
	this->game = game;

	repaint();

	// TODO fill map with game data
}

/**
 * Destructor.
 */
WinPlayground::~WinPlayground(void)
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
WinPlayground::process(int input)
{
	switch(input) {
		case 10: // ENTER
			return WINDOW_PROMPT;
		case ':':
			return WINDOW_PROMPT_COMMAND;
		default:
			return WINDOW_IDENTITY;
	}
}

/**
 * This method defines what happens if this window gains focus.
 */
void
WinPlayground::focus(void)
{
	repaint();
	curs_set(0);
}

/**
 * This method defines what happens if this window loses focus.
 * @return False if this window shall be destroyed, otherwise true.
 */
bool
WinPlayground::unfocus(void)
{
	return true;
}

/**
 * This method repaints the window.
 */
void
WinPlayground::repaint(void)
{
	setBG(22);

	// TODO

	refresh();
}

