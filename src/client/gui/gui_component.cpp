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

	active = -1;
	is_active = false;
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
	for(size_t i = 0; i < components.size(); i++)
		components[i]->handleMouseMotion(x, y);
}

/**
 * Trigger action on mouse click.
 * @param button Mouse button bytemask.
 * @param x      X position of mouse.
 * @param y      Y position of mouse.
 * @return       The name of the next component to focus on.
 */
GUIComponentName
GUIComponent::handleMouseClick(Uint8 button, int x, int y)
{
	for(size_t i = 0; i < components.size(); i++)
		components[i]->handleMouseClick(button, x, y);
	return GUI_COMPONENT_THIS;
}

/**
 * Trigger action on pressed key.
 * @param keys The pressed key.
 * @return     The name of the next component to focus on.
 */
GUIComponentName
GUIComponent::handleKeyPress(Uint8* keys)
{
	// if there's no component, skip:
	if(components.size() == 0)
		return GUI_COMPONENT_NEXT;
	
	if(active >= 0) {
		GUIComponentName next = components[active]->handleKeyPress(keys);
		switch(next) {
			case GUI_COMPONENT_NONE:
				return GUI_COMPONENT_THIS;
			case GUI_COMPONENT_NEXT:
				active = (active+1)%components.size();
				components[active]->focus();
				return GUI_COMPONENT_THIS;
			case GUI_COMPONENT_PREVIOUS:
				active = (active+components.size()-1)%components.size();
				components[active]->focus();
				return GUI_COMPONENT_THIS;
			default:
				return next;
		}
	} else {
		if(keys[SDLK_TAB]) {
			active = 0;
			components[active]->focus();
		}
		return GUI_COMPONENT_THIS;
	}
}

/**
 * Effect when focused.
 */
void
GUIComponent::focus(void)
{
	is_active = true;
}

/**
 * Effect when unfocused.
 */
void
GUIComponent::unfocus(void)
{
	is_active = false;
}

