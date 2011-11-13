/* This is the window manager for the ncurses client.
 */

#ifndef _WM_H_
#define _WM_H_

// UI:
#include "vars.h"
#include "prompt.h"
#include "playground.h"

// Client:
#include "../game.h"
#include "../pipe.h"

// Others:
#include <ncurses.h>

class
WM
{
	public:
		WM(Pipe* pipe, Game* game);
		~WM(void);
		void process(int input);
		void process(char const* msg);
	
	private:
		Pipe* pipe;
		Game* game;
		Window* playground;
		Window* prompt;
		Window* infobar;
		Window* actionbar;
		Window* login;
		Window* menu;
		Window* options;
		Window* navigation;
		Window* social;
		Window* inventory;
		Window* active;     // virtual; points to the currently focused window
};

#endif

