#ifndef _PROMPT_H_
#define _PROMPT_H_

// Parent class:
#include "window.h"

// Client:
#include "../game.h"
#include "../pipe.h"

// Others:
#include <vector>

#define PROMPT_SIZE 80

class
Prompt : public Window
{
	public:
		Prompt(Pipe* pipe, Game* game);
		~Prompt(void);
		/*virtual*/ WindowName process(int input);
		/*virtual*/ void focus(void);
		/*virtual*/ bool unfocus(void);
	
	private:
		Pipe* pipe;
		Game* game;
		std::vector<int> prompt;
		unsigned int cursor_pos;
};

#endif

