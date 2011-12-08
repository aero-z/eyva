/*
 * EYVA - basic GUI element
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

#include "gui_element.h"

/**
 * @param x   X position.
 * @param y   Y position.
 * @param w   Width.
 * @param h   Height.
 * @param dst Surface on which will be drawn.
 */
GUIElement::GUIElement(int x, int y, int w, int h, SDL_Surface* dst)
{
	this->dst = dst;
	rectangle = new SDL_Rect();
	rectangle->x = x;
	rectangle->y = y;
	rectangle->h = h;
	rectangle->w = w;
	surface = newSurface(SDL_HWSURFACE | SDL_DOUBLEBUF, w, h, dst);
	SDL_BlitSurface(surface, NULL, dst, rectangle);
}

GUIElement::~GUIElement(void)
{
	SDL_FreeSurface(surface);
}


/* PROTECTED METHODS */


/**
 * Create a new SDL surface.
 * @param flags Flags to be given to the surface.
 * @param w     Width.
 * @param h     Height.
 * @param dst   The surface whose format the new one shall match.
 */
SDL_Surface*
GUIElement::newSurface(Uint32 flags, int w, int h, const SDL_Surface* dst)
{
	// use the same format as the destination, to avoid conversion time:
	const SDL_PixelFormat* f = dst->format;
	return SDL_CreateRGBSurface(flags, w, h,
			f->BitsPerPixel, f->Rmask, f->Gmask, f->Bmask, f->Amask);
}

