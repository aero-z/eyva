/*
 * EYVA - graphical user interface
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

#include "gui.h"

using namespace AyeLog;
using namespace GUIUtils;

GUI::GUI(void)
{
	pipe = new Pipe();
	term_signal = false;

	// set up SDL and TTF:
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		throw new Exception("SDL_Init() failed");
	if(!TTF_WasInit() && TTF_Init() < 0)
		throw new Exception("TTF_Init() failed");

	// set up surface and event handling:
	event = new SDL_Event();
	root = SDL_SetVideoMode(800, 600, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(root == NULL)
		throw new Exception("SDL_SetVideoMode() failed");
	
	// set window caption (TODO get rid of memory leaks:
	/*
	char caption[256]; // should be enough ...
	snprintf(caption, 256, "eyva [build %d.%d.%d-%d]",
			VERSION_MAJOR_RELEASE, VERSION_MINOR_RELEASE,
			VERSION_MAJOR_PATCH, VERSION_MINOR_PATCH);
	SDL_WM_SetCaption(caption, caption);
	*/
	
	// components:
	components.insert(std::pair<GUIComponentName, GUIComponent*>(
			GUI_COMPONENT_LOGIN, new Login(root, 0, 0, 800, 600)));

	// focus login screen at the start:
	active = GUI_COMPONENT_LOGIN;

	SDL_Flip(root);
}

GUI::~GUI(void)
{
	Network::disconnect();
	delete pipe;
	delete event;
	components.clear();
	SDL_FreeSurface(root);
	
	TTF_Quit();
	SDL_Quit();
}


/* PUBLIC METHODS */


/**
 * Initiate the game loop.
 */
void
GUI::run(void)
{
	while(!term_signal) {
		while(SDL_PollEvent(event)) {
			handleEvents();
		}
		SDL_Flip(root);
		SDL_Delay(50);
	}
}


/* PRIVATE METHODS */


/**
 * Handle an input event.
 */
void
GUI::handleEvents(void)
{
	switch(event->type) {
		case SDL_QUIT:
			term_signal = true;
			break;
		case SDL_KEYDOWN:
			if(active != GUI_COMPONENT_NONE) {
				GUIComponentName next = components[active]->handleKeyPress(
						SDL_GetKeyState(NULL));
				switch(next) {
					case GUI_COMPONENT_THIS:     // don't do anything
					case GUI_COMPONENT_NEXT:     // not supposed to happen
					case GUI_COMPONENT_PREVIOUS: // not supposed to happen
						break;
					default:
						active = next;
						components[active]->focus();
						break;
				}
			}
			break;
		case SDL_MOUSEMOTION: {
			int x, y;
			SDL_GetMouseState(&x, &y);
			for(it = components.begin(); it != components.end(); it++)
				it->second->handleMouseMotion(x, y);
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
			int x, y;
			Uint8 button = SDL_GetMouseState(&x, &y);
			for(it = components.begin(); it != components.end(); it++)
				it->second->handleMouseClick(button, x, y);
			break;
		}
		default:
			break;
	}
}

