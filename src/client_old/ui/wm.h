/*
 * `eyva' (client, UI) window manager for ncurses client
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

#ifndef _UI_WM_H_
#define _UI_WM_H_

// UI:
#include "vars.h"
#include "game.h"
//#include "login.h"
//#include "menu.h"
//#include "options.h"
//#include "navigation.h"
//#include "social.h"
//#include "inventory.h"
//#include "character.h"

// Client:
#include "../game.h"
#include "../pipe.h"

// Others:
#include <ncurses.h>

class
WM
{
	public:
		WM(Pipe* pipe, Game* game);
		~WM(void);
		bool process(int input);
		void process(char const* msg);
	
	private:
		Pipe* pipe;
		Game* game;
		Window* win_game;
		Window* login;
		Window* menu;
		Window* options;
		Window* navigation;
		Window* social;
		Window* character;
		Window* active;     // virtual; points to the currently focused window
};

#endif

