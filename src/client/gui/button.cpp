/*
 * EYVA - clickable button
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

#include "button.h"

/**
 * @param x     X position.
 * @param y     Y position.
 * @param w     Width.
 * @param h     Height.
 * @param dst   Surface on which will be drawn.
 * @param label Label.
 */
Button::Button(int x, int y, int w, int h, SDL_Surface* dst,
		char const* label)
		: GUIElement(x, y, w, h, dst)
{
	this->label = new char[strlen(label)+1]; // +1 for \0
	strcpy(this->label, label);

	// TODO print text on button:
	SDL_FillRect(dst, rectangle, SDL_MapRGB(dst->format, 255, 255, 255));
}

Button::~Button(void)
{
	delete[] label;
}

