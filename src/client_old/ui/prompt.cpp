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

#include "prompt.h"

/**
 * Constructor.
 * @param pipe Allows communication with the network object.
 * @param game Handles and stores game data.
 */
WinPrompt::WinPrompt(Pipe* pipe) :
		Window(0, 21, 80, 1)
{
	this->pipe = pipe;

	repaint();
}

/**
 * Destructor.
 */
WinPrompt::~WinPrompt(void)
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
WinPrompt::process(int input)
{
	WindowName next_win = WINDOW_IDENTITY;

	switch(input) {
		case 10: // newline
			next_win = evaluate();
			prompt.clear();
			cursor_pos = 0;  // not necessary, but secure
			return next_win;
		case 27: //escape
			prompt.clear();
			cursor_pos = 0;  // not necessary, but secure
			break;
		case 127: //backslash
		case 263: //backslash (xterm and virtual terminals)
			if(cursor_pos > 0)
				prompt.erase(prompt.begin()+(--cursor_pos));
			break;
		case 260: //left arrow key
			if(cursor_pos > 0)
				cursor_pos--;
			break;
		case 261: //right arrow key
			if(cursor_pos < prompt.size())
				cursor_pos++;
			break;
		case 262: //home
			cursor_pos = 0;
			break;
		case 330: //delete
			if(cursor_pos < prompt.size())
				prompt.erase(prompt.begin()+cursor_pos);
			break;
		case 360: //end
			cursor_pos = prompt.size();
			break;

		/* Ignore these:
		 */
		case 9: // tabulator
		case 265: // F1
		case 266: // F2
		case 267: // F3
		case 268: // F4
		case 269: // F5
		case 270: // F6
		case 271: // F7
		case 272: // F8
		case 273: // F9
		case 274: // F10
		case 275: // F11
		case 276: // F12
		case 258: // down arrow key (TODO history)
		case 259: // up arrow key (TODO history)
		case 331: // insert
		case 338: // page down
		case 339: // page up
			break;

		default:
			if(prompt.size() < PROMPT_SIZE)
				prompt.insert(prompt.begin()+(cursor_pos++), input);
			break;
	}
	
	/* Update prompt display:
	 */
	repaint(); // not to display relicts
	attron(COLOR_PAIR(10));
	for(size_t i = 0; i < prompt.size(); i++)
		mvprintw(ypos, xpos+i, "%s", &(prompt[i]));
	attroff(COLOR_PAIR(10));

	/* Update cursor position and print out:
	 */
	move(ypos, xpos+cursor_pos);
	refresh();

	/* If the buffer is empty, unfocus:
	 */
	return prompt.size() > 0 ? WINDOW_IDENTITY : WINDOW_PLAYGROUND;
}

/**
 * This method describes what happens when the window gains focus.
 */
void
WinPrompt::focus(void)
{
	repaint();

	/* Set cursor:
	 */
	cursor_pos = 0;
	move(ypos, xpos+cursor_pos);
	curs_set(1);

	refresh();
}

/**
 * This method describes what happens when the window loses focus.
 * @return True if the window is persistent, false if the window shall be
 *         destroyed.
 */
bool
WinPrompt::unfocus(void)
{
	// TODO draw underlying window (actionbar) correctly

	/* Don't display anymore:
	 */
	return false;
}

/**
 * This method repaints the window.
 */
void
WinPrompt::repaint(void)
{
	setBG(10);

	refresh();
}


/* PRIVATE METHODS */


/**
 * This method evaluates the prompt buffer.
 * @return The name of the window that shall be focused next. Since this method
 *         is called by the process() method, that one should forward it back to
 *         its caller.
 */
WindowName
WinPrompt::evaluate(void)
{
	// TODO let the menu handle this (logout etc.)
	if(cmdcmp(":q"))
		return WINDOW_TERM;
	
	// TODO

	return WINDOW_PLAYGROUND;
}

/**
 * This method checks if the command (first word) in the buffer is equal to a
 * specific value.
 * @param keyword The command to be checked.
 * @return        True if the command is equal to the keyword, otherwise false.
 */
bool
WinPrompt::cmdcmp(char const* keyword)
{
	bool equal = (strlen(keyword) <= prompt.size());
	for(size_t i = 0; i < strlen(keyword) && i < prompt.size(); i++)
		if(keyword[i] != prompt[i]) {
			equal = false;
			break;
		}
	
	return equal;
}

/**
 * This method counts the number of arguments in the prompt buffer.
 * @return The number of arguments in the prompt buffer.
 */
int
WinPrompt::argcount(void)
{
	// TODO
	return 0;
}

/**
 * This method fetches a specific argument from the prompt buffer.
 * @param buffer The C string buffer where the argument shall be stored to.
 * @param pos    The index of the argument.
 * @return       The size of the argument.
 */
size_t
WinPrompt::argfetch(char* buffer, int pos)
{
	// TODO
	return 0;
}

