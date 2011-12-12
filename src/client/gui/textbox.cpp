/*
 * EYVA - textbox element for GUI
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

#include "textbox.h"

Textbox::Textbox(SDL_Surface* root, int x, int y, int w, int h,
		char const* name)
		: GUIComponent(root, x, y, w, h)
{
	this->name = new char[strlen(name)+1]; // +1 for \0
	strcpy(this->name, name);
	active = false;

	// TODO dynamically set font size:
	textlabel = new Textlabel(root, TOP_LEFT, x+2, y+2, name, 20,
			180, 180, 180, 255);
	SDL_FillRect(root, rectangle, SDL_MapRGB(root->format, 255, 255, 255));
	textlabel->print();
}

Textbox::~Textbox(void)
{
	delete textlabel;
}


/* PUBLIC METHDODS */


/**
 * React on a clicked mouse button.
 * @param button Mouse button code.
 * @param x      X position.
 * @param y      Y position.
 */
void
Textbox::handleMouseClick(Uint8 button, int x, int y)
{
	bool old_active = active;
	active = x >= rectangle->x && x <= rectangle->x+rectangle->w
			&& y >= rectangle->y && y <= rectangle->y+rectangle->h;

	// if the state has changed, redraw:
	if(old_active != active) {
		if(active) {
			SDL_FillRect(root, rectangle,
					SDL_MapRGB(root->format, 255, 255, 180));
			textlabel->updateColor(0, 0, 0, 255);
			textlabel->print();
		} else {
			SDL_FillRect(root, rectangle,
					SDL_MapRGB(root->format, 255, 255, 255));
			textlabel->updateColor(180, 180, 180, 255);
			textlabel->print();
		}
		textlabel->print();
	}

	// TODO cursor position
}

/**
 * React on a pressed key.
 * @param keys The key code to be handled.
 */
void
Textbox::handleKeyPress(Uint8* keys)
{
	// TODO
}

