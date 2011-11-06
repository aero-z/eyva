/* This is the window manager for the ncurses client.
 */

#ifndef _NCURSES_WM_H_
#define _NCURSES_WM_H_

#include <ncurses.h>
#include <vector>

class
NCursesWM
{
	public:
		NCursesWM(void);
		~NCursesWM(void);
		void process(char input);
	
	private:
		std::vector<WINDOW*> windows;
		WINDOW* focused;
};

#endif

