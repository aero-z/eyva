#ifndef _UI_H_
#define _UI_H_

// Client:
#include "wm.h"
#include "../postmaster.h"

// Utils:
#include <utils/exception.h>
#include <utils/ayelog.h>

// Others:
#include <ncurses.h>
#include <cstdio>

class
UI
{
	public:
		UI(Postmaster* pm);
		~UI(void);
		void poll(double timeout);

	private:
		void pollNetwork(void);
		void pollInput(double timeout);

		WM* wm;
		Postmaster* pm;
		char buffer_text[BUFFER_SIZE];
};

#endif

