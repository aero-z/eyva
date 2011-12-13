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
 * @param root  Surface on which will be drawn.
 * @param x     X position.
 * @param y     Y position.
 * @param w     Width.
 * @param h     Height.
 * @param label Label.
 */
Button::Button(SDL_Surface* root, int x, int y, int w, int h, char const* label)
		: GUIComponent(root, x, y, w, h)
{
	hover = false;

	textlabel = new Textlabel(root, MIDDLE_CENTER, x+w/2, y+h/2, label, 16,
			255, 255, 255, 255);
	SDL_FillRect(root, rectangle, SDL_MapRGB(root->format, 80, 80, 80));
	textlabel->print();
}

Button::~Button(void)
{
	delete textlabel;
}

/**
 * Handle mouse motion.
 * @param x X position of mouse.
 * @param y Y position of mouse.
 */
void
Button::handleMouseMotion(int x, int y)
{
	bool old_hover = hover;
	hover = x >= rectangle->x && x <= rectangle->x+rectangle->w
			&& y >= rectangle->y && y <= rectangle->y+rectangle->h;

	// if the state has changed, redraw:
	if(old_hover != hover) {
		if(hover)
			SDL_FillRect(root, rectangle, SDL_MapRGB(root->format, 0, 0, 0));
		else
			SDL_FillRect(root, rectangle, SDL_MapRGB(root->format, 80, 80, 80));
		textlabel->print();
	}
}

