/* This is the window manager for the ncurses client.
 */

#ifndef _WM_H_
#define _WM_H_

// UI
#include "panel.h"

// Others
#include <ncurses.h>

class
WM
{
	public:
		WM(void);
		~WM(void);
		void process(int input);
	
	private:
		Window* panel;  // bottom panel
		Window* world;  // "main" window
		Window* social; // chat etc.
		Window* map;    // orientation map
		Window* menu;   // character overview, options, etc.
		Window* login;  // login dialog
		Window* focus;
};

#endif

