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

#include "gui_component.h"

using namespace GUIUtils;

/**
 * @param root Surface on which will be drawn.
 * @param x    X position.
 * @param y    Y position.
 * @param w    Width.
 * @param h    Height.
 */
GUIComponent::GUIComponent(SDL_Surface* root, int x, int y, int w, int h)
{
	this->root = root;
	rectangle = new SDL_Rect();
	rectangle->x = x;
	rectangle->y = y;
	rectangle->h = h;
	rectangle->w = w;
}

GUIComponent::~GUIComponent(void)
{
	components.clear();
	delete rectangle;
}


/* PUBLIC METHODS */


/**
 * Trigger action on mouse motion.
 * @param x X position of mouse.
 * @param y Y position of mouse.
 */
void
GUIComponent::handleMouseMotion(int x, int y)
{
	for(it = components.begin(); it != components.end(); it++)
		it->second->handleMouseMotion(x, y);
}

/**
 * Trigger action on mouse click.
 * @param button Mouse button bytemask.
 * @param x      X position of mouse.
 * @param y      Y position of mouse.
 */
void
GUIComponent::handleMouseClick(Uint8 button, int x, int y)
{
	for(it = components.begin(); it != components.end(); it++)
		it->second->handleMouseClick(button, x, y);
}

/**
 * Trigger action on pressed key.
 * @param keys The pressed key.
 */
void
GUIComponent::handleKeyPress(Uint8* keys)
{
	for(it = components.begin(); it != components.end(); it++)
		it->second->handleKeyPress(keys);
}

