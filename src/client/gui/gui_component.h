/*
 * EYVA - basic GUI element
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

#ifndef _GUI_COMPONENT_H_
#define _GUI_COMPONENT_H_

#include "gui_utils.h"

#include <SDL/SDL.h>
#include <vector>

class
GUIComponent
{
	public:
		GUIComponent(SDL_Surface* root, int x, int y, int width, int height);
		virtual ~GUIComponent(void);
		virtual void handleMouseMotion(int x, int y);
		virtual GUIComponentName handleMouseClick(Uint8 button, int x, int y);
		virtual GUIComponentName handleKeyPress(Uint8* keys);
	
	protected:
		SDL_Rect* rectangle;
		SDL_Surface* root;
		SDL_Surface* local;
		std::vector<GUIComponent*> components;
		int active;
};

#endif

