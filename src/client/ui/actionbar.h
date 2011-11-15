#ifndef _UI_ACTIONBAR_H_
#define _UI_ACTIONBAR_H_

// Parent class:
#include "window.h"

// Client:
#include "../game.h"

class
WinActionbar : public Window
{
	public:
		WinActionbar(Game* game);
		~WinActionbar(void);
		/*virtual*/ WindowName process(int input);
		/*virtual*/ void focus(void);
		/*virtual*/ bool unfocus(void);
		/*virtual*/ void repaint(void);

	private:
		Game* game;
};

#endif

