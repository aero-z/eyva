#ifndef _BOTTOM_PANEL_H_
#define _BOTTOM_PANEL_H_

// Parent class:
#include "window.h"

// Client:
#include "../game.h"
#include "../pipe.h"

// Others:
#include <vector>

#define PROMPT_SIZE 80

class
BottomPanel : public Window
{
	public:
		BottomPanel(Pipe* pipe, Game* game);
		~BottomPanel(void);
		/*virtual*/ WindowName process(int input);
		/*virtual*/ void focus(void);
		/*virtual*/ bool unfocus(void);
	
	private:
		Pipe* pipe;
		Game* game;
		std::vector<char> prompt;
		unsigned int cursor_pos;
};

#endif

