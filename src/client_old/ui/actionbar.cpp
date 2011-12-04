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

#include "actionbar.h"

/**
 * Constructor.
 * @param game The game that handles and holds all game related data.
 */
WinActionbar::WinActionbar(Game* game) :
		Window(0, 21, 80, 3)
{
	this->game = game;

	repaint();
}

/**
 * Destructor.
 */
WinActionbar::~WinActionbar(void)
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
WinActionbar::process(int input)
{
	return WINDOW_PLAYGROUND;
}

/**
 * This method defines the behaviour of the window when focused. Since this is
 * the actionbar (and thus never focused), it won't do anything.
 */
void
WinActionbar::focus(void)
{
	// VOID
}

/**
 * This method defines the behaviour of the window when unfocused. Since this is
 * the actionbar (and thus never (un)focused), it won't do anything.
 * @return False if the window shall be destroyed at unfocusing, otherwise true.
 */
bool
WinActionbar::unfocus(void)
{
	return true;
}

/**
 * This method repaints the window.
 */
void
WinActionbar::repaint(void)
{
	setBG(11);

	refresh();
}

