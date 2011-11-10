#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <ncurses.h>

enum Color {
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
};

class
Window
{
	public:
		Window(int xpos, int ypos, int width, int height);
		virtual bool process(int input);
		virtual void focusWindow(void);
		virtual bool unfocusWindow(void);
		void moveWindow(int xpos, int ypos);
		void resizeWindow(int width, int height);
	
	protected:
		void printch(int x, int y, char c, Color fg, Color bg);
		int xpos, ypos;   // upper left corner position
		int width, height;
};

#endif

