#ifndef _NCURSES_UI_
#define _NCURSES_UI_

#include "ui.h"
#include "ncurses_wm.h"
#include <exception.h>

#include <ncurses.h>
#include <cstdio>    // (v)(s)(f)(n)printf
#include <cstdarg>   // va_list

class NCursesUI : public UI {
	public:
		NCursesUI(void);
		~NCursesUI(void);

		// virtual:
		void pollInput(char* buffer_out, double timeout);
		bool prompt(char const* format, ...);

	private:
		NCursesWM* wm;
		char buffer_text[BUFFER_SIZE];
};

#endif

