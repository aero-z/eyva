#ifndef _PLAYGROUND_H_
#define _PLAYGROUND_H_

// Parent class:
#include "window.h"

// Client:
#include "../game.h"
#include "../pipe.h"

class
Playground : public Window
{
	public:
		Playground(Pipe* pipe, Game* game);
		~Playground(void);
		/*virtual*/ WindowName process(int input);
		/*virtual*/ void focus(void);
		/*virtual*/ bool unfocus(void);
	
	private:
		Game* game;
		Pipe* pipe;
};

#endif

