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
 * @return       The name of the next window to be focused.
 */
GUIComponentName
Textbox::handleMouseClick(Uint8 button, int x, int y)
{
	bool was_active = is_active;
	is_active = x >= rectangle->x && x <= rectangle->x+rectangle->w
			&& y >= rectangle->y && y <= rectangle->y+rectangle->h;

	// if the state has changed, redraw:
	if(was_active != is_active) {
		if(is_active)
			focus();
		else
			unfocus();
	}

	return is_active ? GUI_COMPONENT_THIS : GUI_COMPONENT_NONE;
}

/**
 * React on a pressed key.
 * @param keys The key code to be handled.
 * @return     The name of the next window to be focused.
 */
GUIComponentName
Textbox::handleKeyPress(Uint8* keys)
{
	if(keys[SDLK_TAB]) {
		unfocus();
		return GUI_COMPONENT_NEXT;
	}
	if(keys[SDLK_ESCAPE]) {
		unfocus();
		return GUI_COMPONENT_NONE;
	}
	return GUI_COMPONENT_THIS;
}

/**
 * Effect when focused.
 */
void
Textbox::focus(void)
{
	SDL_FillRect(root, rectangle,
			SDL_MapRGB(root->format, 255, 255, 180));
	textlabel->updateColor(0, 0, 0, 255);
	char* c_input = new char[input.size()+1]; // +1 for \0
	for(size_t i = 0; i < input.size(); i++)
		c_input[i] = input[i]->getCharacter();
	c_input[input.size()] = 0;
	textlabel->updateLabel(c_input);
	delete[] c_input;
	textlabel->print();
	is_active = true;
}

/**
 * Effect when unfocused.
 */
void
Textbox::unfocus(void)
{
	SDL_FillRect(root, rectangle,
			SDL_MapRGB(root->format, 255, 255, 255));
	textlabel->updateColor(180, 180, 180, 255);
	if(input.size() == 0)
		textlabel->updateLabel(name);
	textlabel->print();
	is_active = false;
}

