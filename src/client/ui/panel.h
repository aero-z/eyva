#ifndef _PANEL_H_
#define _PANEL_H_

// Parent class:
#include "window.h"

// Client:
#include "../game.h"
#include "../pipe.h"

// Others:
#include <vector>

#define PROMPT_SIZE 80

class
Panel : public Window
{
	public:
		Panel(Pipe* pipe, Game* game);
		~Panel(void);
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

