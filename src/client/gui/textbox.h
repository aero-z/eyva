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

#ifndef _TEXTBOX_H_
#define _TEXTBOX_H_

#include "gui_component.h"
#include "textbox_character.h"
#include "textlabel.h"

#include <vector>

class
Textbox : public GUIComponent
{
	public:
		Textbox(SDL_Surface* root, int x, int y, int w, int h,
				char const* name);
		~Textbox(void);
		GUIComponentName handleMouseClick(Uint8 button, int x, int y);
		GUIComponentName handleKeyPress(Uint8* keys);
		void focus(void);
		void unfocus(void);
	
	protected:
		char* name;
		std::vector<TextboxCharacter*> input;
		Textlabel* textlabel;
		int cursor_pos;
};

#endif

