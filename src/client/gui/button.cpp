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
 * @param root  Surface on which will be drawn.
 * @param label Label.
 */
Button::Button(int x, int y, int w, int h, SDL_Surface* root,
		char const* label)
		: GUIComponent(x, y, w, h, root)
{
	this->label = new char[strlen(label)+1]; // +1 for \0
	strcpy(this->label, label);

	// TODO print text on button:
	SDL_FillRect(root, rectangle, SDL_MapRGB(root->format, 80, 80, 80));
}

Button::~Button(void)
{
	delete[] label;
}

/**
 * Handle mouse motion.
 * @param x X position of mouse.
 * @param y Y position of mouse.
 */
void
Button::handleMouseMotion(int x, int y)
{
	bool hover = x > rectangle->x && x < rectangle->x+rectangle->w
			&& y > rectangle->y && y < rectangle->y+rectangle->h;

	if(hover == true)
		SDL_FillRect(root, rectangle, SDL_MapRGB(root->format, 0, 0, 0));
	else
		SDL_FillRect(root, rectangle, SDL_MapRGB(root->format, 80, 80, 80));
}

