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

#include "textbox_character.h"

TextboxCharacter::TextboxCharacter(char c)
{
	this->c = c;
}

TextboxCharacter::~TextboxCharacter(void)
{
}


/* PUBLIC METHODS */


/**
 * @return The character.
 */
char
TextboxCharacter::getCharacter(void)
{
	return c;
}

/**
 * Toggles if the character is selected.
 */
void
TextboxCharacter::toggleSelected(void)
{
	selected = !selected;
}

/**
 * @return True if selected, otherwise false.
 */
bool
TextboxCharacter::isSelected(void)
{
	return selected;
}

