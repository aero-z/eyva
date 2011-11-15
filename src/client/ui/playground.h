#ifndef _UI_PLAYGROUND_H_
#define _UI_PLAYGROUND_H_

// Parent class:
#include "window.h"

// Client:
#include "../game.h"
#include "../pipe.h"

class
WinPlayground : public Window
{
	public:
		WinPlayground(Pipe* pipe, Game* game);
		~WinPlayground(void);
		/*virtual*/ WindowName process(int input);
		/*virtual*/ void focus(void);
		/*virtual*/ bool unfocus(void);
		/*virtual*/ void repaint(void);
	
	private:
		Game* game;
		Pipe* pipe;
};

#endif

