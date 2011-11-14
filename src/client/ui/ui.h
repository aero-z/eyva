#ifndef _UI_H_
#define _UI_H_

// UI:
#include "wm.h"

// Client:
#include "../pipe.h"
#include "../game.h"

// Utils:
#include <utils/exception.h>
#include <utils/ayelog.h>

// Others:
#include <ncurses.h>
#include <cstdio>
#include <clocale>
#include <cstdlib>

class
UI
{
	public:
		UI(Pipe* pipe, Game* game);
		~UI(void);
		void poll(double timeout);
		void process(char const* msg);
		bool checkTermSignal(void);

	private:
		void pollInput(double timeout);

		WM* wm;
		Pipe* pipe;
		Game* game;
		bool term_signal;
};

#endif

