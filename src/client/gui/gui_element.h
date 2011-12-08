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

#ifndef _GUI_ELEMENT_H_
#define _GUI_ELEMENT_H_

#include <SDL/SDL.h>

class
GUIElement
{
	public:
		GUIElement(int x, int y, int width, int height, SDL_Surface* dst);
		virtual ~GUIElement(void);
	
	protected:
		SDL_Surface* newSurface(Uint32 flags, int w, int h,
				const SDL_Surface* dst);

		SDL_Rect* rectangle;
		SDL_Surface* surface;
		SDL_Surface* dst;
};

#endif

