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
		virtual ~Window(void);
		virtual WindowName process(int input) = 0;
		virtual void focus(void) = 0;
		virtual bool unfocus(void) = 0;
		void moveWindow(int xpos, int ypos);
		void draw(void);
	
	protected:
		void initColors(void);
		void setBG(int color);

		int xpos, ypos;   // upper left corner position
		int width, height;
};

#endif

