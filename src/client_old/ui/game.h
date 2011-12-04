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

#ifndef _UI_GAMEWIN_H_
#define _UI_GAMEWIN_H_

// Parent class:
#include "window.h"

// UI:
#include "playground.h"
#include "prompt.h"
#include "actionbar.h"
//#include "infobar.h"
//#include "inventory.h"

// Client:
#include "../pipe.h"
#include "../game.h"

class
WinGame: public Window
{
	public:
		WinGame(Pipe* pipe, Game* game);
		~WinGame(void);
		/*virtual*/ WindowName process(int input);
		/*virtual*/ void focus(void);
		/*virtual*/ bool unfocus(void);
		/*virtual*/ void repaint(void);
	
	private:
		Window* playground;
		Window* actionbar;
		Window* active;
		Pipe* pipe;
		Game* game;
};

#endif

