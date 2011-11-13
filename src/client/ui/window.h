#ifndef _WINDOW_H_
#define _WINDOW_H_

// UI:
#include "vars.h"
#include "content.h"

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
		void printch(int x, int y, char c, int color);
		void initColors(void);

		int xpos, ypos;   // upper left corner position
		int width, height;
		Content* content;
};

#endif

