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

#ifndef _UI_WINDOW_H_
#define _UI_WINDOW_H_

// UI:
#include "vars.h"

// Utils:
#include <utils/exception.h>

// Others:
#include <ncurses.h>

class
Window
{
	public:
		Window(int xpos, int ypos, int width, int height);
		virtual ~Window(void);
		virtual WindowName process(int input) = 0;
		virtual void focus(void) = 0;
		virtual bool unfocus(void) = 0;
		virtual void repaint(void) = 0;
		void moveWindow(int xpos, int ypos);
		void draw(void);
	
	protected:
		void initColors(void);
		void setBG(int color);

		int xpos, ypos;   // upper left corner position
		int width, height;
};

#endif

