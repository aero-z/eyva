/* This is the window manager for the ncurses client.
 */

#ifndef _WM_H_
#define _WM_H_

#include <ncurses.h>
#include <vector>

class
WM
{
	public:
		WM(void);
		~WM(void);
		void process(char input);
	
	private:
		std::vector<WINDOW*> windows;
		WINDOW* focused;
};

#endif

