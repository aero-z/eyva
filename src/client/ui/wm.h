/* This is the window manager for the ncurses client.
 */

#ifndef _WM_H_
#define _WM_H_

// UI:
#include "panel.h"

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
		Window* map;        // "main" window
		Window* panel;      // bottom panel [':']
		Window* social;     // chat etc. [TAB -> right]
		Window* navigation; // orientation map ['m' -> top]
		Window* menu;       // character overview, options, etc. [ESC -> bottom]
		Window* login;      // login dialog
		Window* focus;
};

#endif

