#ifndef _NCURSES_UI_
#define _NCURSES_UI_

#include "ui.h"

class NCursesUI : public UI {
	public:
		NCursesUI(void);
		bool pollInput(command com, double timeout);
};

#endif

