/* This is the window manager for the ncurses client.
 */

#ifndef _UI_WM_H_
#define _UI_WM_H_

// UI:
#include "vars.h"
#include "game.h"
//#include "login.h"
//#include "menu.h"
//#include "options.h"
//#include "navigation.h"
//#include "social.h"
//#include "inventory.h"
//#include "character.h"

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
		bool process(int input);
		void process(char const* msg);
	
	private:
		Pipe* pipe;
		Game* game;
		Window* win_game;
		Window* login;
		Window* menu;
		Window* options;
		Window* navigation;
		Window* social;
		Window* character;
		Window* active;     // virtual; points to the currently focused window
};

#endif

