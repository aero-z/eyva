#ifndef _WINDOW_H_
#define _WINDOW_H_

// UI:
#include "vars.h"

// Utils:
#include <utils/exception.h>

// Others:
#include <ncurses.h>

class
Window
{
	public:
		Window(int xpos, int ypos, int width, int height);
		virtual WindowName process(int input);
		virtual void focus(void);
		virtual bool unfocus(void);
		void moveWindow(int xpos, int ypos);
		void resizeWindow(int width, int height);
	
	protected:
		void printch(int x, int y, char c, int color);
		void initColors(void);

		int xpos, ypos;   // upper left corner position
		int width, height;
};

#endif

