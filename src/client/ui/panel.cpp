#include "panel.h"

/**
 * Constructor.
 * @param pipe Allows communication with the network object.
 * @param game Handles and stores game data.
 */
Panel::Panel(Pipe* pipe, Game* game) :
		Window(0, 21, 80, 3)
{
	this->pipe = pipe;
	this->game = game;

	draw();
}

/**
 * Destructor.
 */
Panel::~Panel(void)
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
Panel::process(int input)
{
	switch(input) {
		case 10: // newline
			// TODO evaluate command
			prompt.clear();
			cursor_pos = 0;  // not necessary, but secure
			break;
		case 27: //escape
			prompt.clear();
			cursor_pos = 0;  // not necessary, but secure
			break;
		case 127: //backslash
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
		case 258: // down arrow key
		case 259: // up arrow key
		case 331: // insert
		case 338: // page down
		case 339: // page up
			break;

		default:
			if(prompt.size() < PROMPT_SIZE)
				prompt.insert(prompt.begin()+(cursor_pos++), input);
			break;
	}
	
	/* First, clear the "background":
	 */
	for(int i = 0; i < PROMPT_SIZE; i++)
		printch(i, 0, ' ', 7);
	
	/* Second, print the buffer content:
	 */
	for(size_t i = 0; i < prompt.size(); i++)
		printch(i, 0, prompt[i], 7);

	/* Third, update the cursor position on the screen and print out:
	 */
	move(ypos, xpos+cursor_pos);
	refresh();

	/* If the buffer is empty, unfocus:
	 */
	return prompt.size() > 0 ? IDENTITY : PLAYGROUND;
}

/**
 * This method describes what happens when the window gains focus.
 */
void
Panel::focus(void)
{
	/* Paint first line background black:
	 */
	for(int x = 0; x < width; x++)
		printch(x, 0, ' ', 7);
	
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
Panel::unfocus(void)
{
	/* TODO reset properly:
	 */
	for(int x = 0; x < width; x++)
		printch(x, 0, ' ', 30);
	
	draw();

	/* Remain persistent:
	 */
	return true;
}

/**
 * This header files handles all cases of user input for the bottom panel.
 */

