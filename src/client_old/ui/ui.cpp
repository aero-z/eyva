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

#include "ui.h"

using namespace AyeLog;

/**
 * Constructor.
 * The ncurses session is started here.
 * @param pipe Used to send messages to the network.
 * @param game Handles and stores game data.
 */
UI::UI(Pipe* pipe, Game* game)
{
	this->pipe = pipe;
	this->game = game;

	logf(LOG_DEBUG, "starting ncurses UI ...");
	logf(LOG_DEBUG, "maximum number of color pairs: %d", COLOR_PAIRS);

	/* TODO supposed to support umlauts and the like, but doesn't work:
	 */
	setlocale(LC_ALL, "");

	initscr();      // start ncurses mode
	wm = new WM(pipe, game);  // our window manager

	/* Set the behaviour of ncurses:
	 */
	cbreak();              // for user input, don't wait for the return
	keypad(stdscr, TRUE);  // allow arrow and F keys
	noecho();              // don't display user input

	term_signal = false;   // this is false as long as the program shall run
}

/**
 * Destructor.
 * The ncurses session is stopped here in order to be able to normally go on
 * with terminal work.
 */
UI::~UI(void)
{
	delete wm;
	endwin();   // end ncurses mode
}


/* PUBLIC METHODS */


/**
 * This is a method defined [virtual] by the UI superclass.
 * It checks for user input and alerts the network handler via postmaster if
 * necessary.
 * @param timeout The delay (or time to wait) for a user input before going on
 *                in seconds.
 */
void
UI::poll(double timeout)
{
	pollInput(timeout);
}

/**
 * This method processes a network message.
 * @param msg The eyva protocol conform message.
 */
void
UI::process(char const* msg)
{
	wm->process(msg);
}

/**
 * This method checks if the term signal is set.
 * @return True if the signal is set, otherwise false.
 */
bool
UI::checkTermSignal(void)
{
	return term_signal;
}


/* PRIVATE METHODS */


/**
 * This method checks for user input and lets the WM handle it.
 * @param timeout The time to block on a user input polling.
 */
void
UI::pollInput(double timeout)
{
	halfdelay((int)(timeout*10));
	int input = getch();
	switch(input) {
		case ERR:
			break;
		default:
			term_signal = wm->process(input);
	}
}

