#ifndef _NCURSES_UI_
#define _NCURSES_UI_

#include "ui.h"
#include "ncurses_wm.h"
#include "../data_handler.h"
#include <exception.h>

#include <ncurses.h>

class
NCursesUI : public UI
{
	public:
		NCursesUI(DataHandler* data_handler);
		~NCursesUI(void);
		void poll(double timeout); // virtual

	private:
		NCursesWM* wm;
		DataHandler* data_handler;
		char buffer_text[BUFFER_SIZE];
};

#endif

