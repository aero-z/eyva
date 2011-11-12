/* This is the window manager for the ncurses client.
 */

#ifndef _WM_H_
#define _WM_H_

// UI:
#include "vars.h"
#include "bottom_panel.h"
#include "playground.h"

// Client:
#include "../game.h"

// Others:
#include <ncurses.h>

class
WM
{
	public:
		WM(void);
		~WM(void);
		void process(int input);
	
	private:
		Game* game;
		Window* playground;
		Window* bottom_panel;
		Window* top_panel;
		Window* login;
		Window* menu;
		Window* options;
		Window* navigation;
		Window* social;
		Window* inventory;
		Window* active;     // virtual; points to the currently focused window
};

#endif

