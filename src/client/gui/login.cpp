/*
 * EYVA - login screen
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

#include "login.h"

/**
 * @param root Surface on which will be drawn.
 * @param x    X position.
 * @param y    Y position.
 * @param w    Width.
 * @param h    Height.
 */
Login::Login(SDL_Surface* root, int x, int y, int w, int h)
		: GUIComponent(root, x, y, w, h)
{
	SDL_FillRect(root, NULL, SDL_MapRGB(root->format, 200, 200, 200));

	// login name input field:
	components.insert(std::pair<GUIComponentName, GUIComponent*>(
			GUI_COMPONENT_INPUT_LOGIN_NAME, new Textbox(root,
					50, 280, 280, 40, "name")));
	// login button:
	components.insert(std::pair<GUIComponentName, GUIComponent*>(
			GUI_COMPONENT_BUTTON_LOGIN_SUBMIT, new Button(root,
					350, 280, 100, 40, "login")));
}

Login::~Login(void)
{
	//delete button_submit;
}

/**
 * Handle mouse motion.
 * @param x X position of the mouse.
 * @param y Y position of the mouse.
 */
void
Login::handleMouseMotion(int x, int y)
{
	components[GUI_COMPONENT_BUTTON_LOGIN_SUBMIT]->handleMouseMotion(x, y);
}

