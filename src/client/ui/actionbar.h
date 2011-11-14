#ifndef _ACTIONBAR_H_
#define _ACTIONBAR_H_

// Parent class:
#include "window.h"

// Client:
#include "../game.h"

class
Actionbar : public Window
{
	public:
		Actionbar(Game* game);
		~Actionbar(void);
		/*virtual*/ WindowName process(int input);
		/*virtual*/ void focus(void);
		/*virtual*/ bool unfocus(void);
		/*virtual*/ void repaint(void);

	private:
		Game* game;
};

#endif

