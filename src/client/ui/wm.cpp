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

#include "wm.h"

/**
 * Constructor.
 */
WM::WM(Pipe* pipe, Game* game)
{
	this->pipe = pipe;
	this->game = game;

	/* Create windows:
	 */
	win_game = new WinGame(pipe, game);
	//login = new WinLogin(pipe);
	//menu = new WinMenu(pipe, game);
	//options = new WinOptions();
	//character = new WinCharacter(pipe, game);
	//social = new WinSocial(pipe, game);
	//navigation = new WinNavigation(game);
	
	active = win_game;
	active->focus();
}

/**
 * Destructor.
 */
WM::~WM(void)
{
	delete win_game;
	//delete login;
	//delete menu;
	//delete options;
	//delete character;
	//delete social;
	//delete navigation;
}


/* PUBLIC METHODS */


/**
 * This method processes a user input (button) by sending it to the currently
 * focused window.
 * @param input The key pressed by the user.
 * @return      The term signal (true if a shutdown command was given, otherwise
 *              false).
 */
bool
WM::process(int input)
{
	/* Let the active window process the input:
	 */
	WindowName next = active->process(input);

	/* If the window name is TERM, the program shall be stopped:
	 */
	if(next == WINDOW_TERM)
		return true;

	/* The processing method will return the name of the next window to be
	 * focused. If the window points to itself, ignore and return:
	 */
	if(next == WINDOW_IDENTITY)
		return false;

	/* Otherwise unfocus and check if the window shall remain persistent. If not
	 * destroy it:
	 */
	if(!active->unfocus())
		delete active;

	switch(next) {
		case WINDOW_GAME:
			active = win_game;
			break;
		default:
			break;
	}

	/* Invoke the focussing process:
	 */
	active->repaint();
	active->focus();
	return false;
}

/**
 * This method processes a network message.
 * @param msg The eyva protocol compliant message to be processed.
 */
void
WM::process(char const* msg)
{
	// TODO animation!
}

