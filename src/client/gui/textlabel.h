/*
 * EYVA - textlabel element
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

#ifndef _TEXTLABEL_H_
#define _TEXTLABEL_H_

#include <generic/utils/exception.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

enum
Alignment
{
	TOP_LEFT,
	TOP_CENTER,
	TOP_RIGHT,
	MIDDLE_LEFT,
	MIDDLE_CENTER,
	MIDDLE_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_CENTER,
	BOTTOM_RIGHT
};

class
Textlabel
{
	public:
		Textlabel(SDL_Surface* root, Alignment alignment, int x, int y,
				char const* label, int size, char r, char g, char b, char a);
		~Textlabel(void);
		void updateLabel(char const* label);
		void print(void);
	
	private:
		SDL_Rect* rectangle;
		SDL_Surface* root;
		SDL_Surface* local;
		TTF_Font* font;
		SDL_Color color;
		char* label;
};

#endif

