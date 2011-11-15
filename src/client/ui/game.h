#ifndef _UI_GAMEWIN_H_
#define _UI_GAMEWIN_H_

// Parent class:
#include "window.h"

// UI:
#include "playground.h"
#include "prompt.h"
#include "actionbar.h"
//#include "infobar.h"
//#include "inventory.h"

// Client:
#include "../pipe.h"
#include "../game.h"

class
WinGame: public Window
{
	public:
		WinGame(Pipe* pipe, Game* game);
		~WinGame(void);
	
	private:
		WinPlayground* playground;
		WinPrompt* prompt;
		WinActionbar* actionbar;
};

#endif

