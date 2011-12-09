/*
 * EYVA - various SDL related functionalities
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

#include "gui_utils.h"

TTF_Font* GUIUtils::font_FreeSans = NULL;


/* PUBLIC METHODS */


/**
 * Get get a text on a surface.
 * @param text Text to be printed.
 * @param size Size of the text.
 */
SDL_Surface*
GUIUtils::printText(char const* text, int size)
{
	if(font_FreeSans == NULL) {
		font_FreeSans = TTF_OpenFont("usr/fonts/FreeSans.ttf", size);
		if(font_FreeSans == NULL)
			return NULL;
	}
	// TODO
	return NULL;
}

