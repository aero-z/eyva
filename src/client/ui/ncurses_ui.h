#ifndef _NCURSES_UI_
#define _NCURSES_UI_

// Client:
#include "ui.h"
#include "ncurses_wm.h"
#include "../postmaster.h"

// Utils:
#include <utils/exception.h>
#include <utils/ayelog.h>

// Others:
#include <ncurses.h>
#include <cstdio>

class
NCursesUI : public UI
{
	public:
		NCursesUI(Postmaster* pm);
		~NCursesUI(void);
		void poll(double timeout); // virtual

	private:
		NCursesWM* wm;
		Postmaster* pm;
		char buffer_text[BUFFER_SIZE];
};

#endif

