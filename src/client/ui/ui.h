/*
 * `eyva'
 * Copyright (C) 2011 ayekat (martin.weber@epfl.ch)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _UI_UI_H_
#define _UI_UI_H_

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

