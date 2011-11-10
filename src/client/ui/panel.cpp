#include "panel.h"

/**
 * Constructor.
 * @param xpos   The window's upper left edge's X coordinate.
 * @param ypos   The window's upper left edge's Y coordinate.
 * @param width  The window's width.
 * @param height The window's height.
 */
Panel::Panel(int xpos, int ypos, int width, int height) :
		Window(xpos, ypos, width, height)
{
	cursor_pos = 0;
}


/* PUBLIC METHODS */


/**
 * This method handles the user input for the panel.
 * @return True if the window shall keep focus, false if it shall lose focus.
 */
bool
Panel::process(int input)
{
	switch(input) {
		case 10: // newline
			// TODO evaluate buffer
			prompt.clear();
			break;
		case 27: //escape
			prompt.clear();
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
		printch(i, 0, ' ', BLACK, WHITE);
	
	/* Second, print the buffer content:
	 */
	for(size_t i = 0; i < prompt.size(); i++)
		printch(i, 0, prompt[i], BLACK, WHITE);

	/* Third, update the cursor position on the screen:
	 */
	move(ypos, xpos+cursor_pos);

	/* Print out! If the buffer is empty, unfocus:
	 */
	refresh();
	return(prompt.size() > 0);
}

/**
 * This method describes what happens when the window gains focus.
 */
void
Panel::focusWindow(void)
{
	curs_set(1);
	cursor_pos = 0;
	move(ypos, xpos+cursor_pos);
	refresh();
}

/**
 * This method describes what happens when the window loses focus.
 * @return True if the window is persistent, false if the window shall be
 *         destroyed.
 */
bool
Panel::unfocusWindow(void)
{
	return true;
}

