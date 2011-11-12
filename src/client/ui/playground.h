#ifndef _PLAYGROUND_H_
#define _PLAYGROUND_H_

// Parent class:
#include "window.h"

// Client:
#include "../game.h"

class
Playground : public Window
{
	public:
		Playground(Game* game);
		~Playground(void);
		/*virtual*/ WindowName process(int input);
		/*virtual*/ void focus(void);
		/*virtual*/ bool unfocus(void);
	
	private:
		Game* game;
};

#endif

