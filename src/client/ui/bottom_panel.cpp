#include "bottom_panel.h"

/**
 * Constructor.
 * @param xpos   The window's upper left edge's X coordinate.
 * @param ypos   The window's upper left edge's Y coordinate.
 * @param width  The window's width.
 * @param height The window's height.
 */
BottomPanel::BottomPanel(Game* game) :
		Window(0, 21, 80, 3)
{
	this->game = game;
	drawContent();
}


/* PUBLIC METHODS */


/**
 * This method handles the user input for the panel.
 * @param input The user's input key.
 * @return      The name of the window that shall be focused next.
 */
WindowName
BottomPanel::process(int input)
{
	switch(input) {
		#include "process_bottom_panel.h"
	}
	
	/* First, clear the "background":
	 */
	for(int i = 0; i < PROMPT_SIZE; i++)
		printch(i, 0, ' ', BLACK, WHITE);
	
	/* Second, print the buffer content:
	 */
	for(size_t i = 0; i < prompt.size(); i++)
		printch(i, 0, prompt[i], WHITE, BLACK);

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
BottomPanel::focus(void)
{
	/* Paint line background black:
	 */
	for(int x = 0; x < width; x++)
		printch(x, 0, ' ', WHITE, BLACK);
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
BottomPanel::unfocus(void)
{
	/* Reset:
	 */
	drawContent();
	
	/* Remain persistent:
	 */
	return true;
}


/* PRIVATE METHODS */


/**
 * This method draws the bottom panel's content.
 */
void
BottomPanel::drawContent(void)
{
	for(int x = 0; x < width; x++)
		for(int y = 0; y < height; y++)
			printch(x, y, ' ', BLACK, YELLOW); // yellow
	
	// TODO display informations
}

