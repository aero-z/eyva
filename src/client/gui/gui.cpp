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
	network = NULL;
	term_signal = false;

	// set up SDL:
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		throw new Exception("SDL_Init() failed");
	
	// set up TTF:
	if(!TTF_WasInit() && TTF_Init() < 0) {
		throw new Exception("TTF_Init() failed");
	}
	
	// set up surface and event handling:
	event = new SDL_Event();
	root = SDL_SetVideoMode(800, 600, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(root == NULL)
		throw new Exception("SDL_SetVideoMode() failed");
	
	// TODO temporary: login screen
	components.insert(std::pair<GUIComponentName, GUIComponent*>(
			GUI_COMPONENT_SCREEN_LOGIN, new Login(0, 0, 800, 600, root)));
	SDL_Flip(root);
}

GUI::~GUI(void)
{
	if(network != NULL)
		delete network;
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
	}
	SDL_Delay(30);
}


/* PRIVATE METHODS */


void
GUI::handleEvents(void)
{
	switch(event->type) {
		case SDL_QUIT:
			term_signal = true;
			break;
		case SDL_KEYDOWN:
			break;
		case SDL_MOUSEMOTION: {
			int x, y;
			SDL_GetMouseState(&x, &y);
			for(it = components.begin(); it != components.end(); it++) {
				it->second->handleMouseMotion(x, y);
			}
		}
		default:
			break;
	}
}

