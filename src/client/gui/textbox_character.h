/*
 * EYVA - element representing a character in a textbox
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

#ifndef _TEXTBOX_CHARACTER_H_
#define _TEXTBOX_CHARACTER_H_

class
TextboxCharacter
{
	public:
		TextboxCharacter(char c);
		~TextboxCharacter(void);
		char getCharacter(void);
		void toggleSelected(void);
		bool isSelected(void);
	
	private:
		char c;
		bool selected;
};

#endif

