#ifndef _PANEL_H_
#define _PANEL_H_

// Parent class:
#include "window.h"

// Client:
#include "../game.h"

// Others:
#include <vector>

#define PROMPT_SIZE 80

class
Panel : public Window
{
	public:
		Panel(Game* game, int xpos, int ypos, int width, int height);
		/*virtual*/ bool process(int input);
		/*virtual*/ void focusWindow(void);
		/*virtual*/ bool unfocusWindow(void);
	
	private:
		Game* game;
		std::vector<char> prompt;
		unsigned int cursor_pos;
};

#endif

