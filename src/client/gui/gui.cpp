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
	surface = SDL_SetVideoMode(800, 600, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	event = new SDL_Event();
	
	// TODO temporary: login screen
	login_screen = new Login(0, 0, 800, 600, surface);
	SDL_Flip(surface);
}

GUI::~GUI(void)
{
	if(network != NULL)
		delete network;
	delete pipe;
	delete event;
	SDL_FreeSurface(surface);
	
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
	}
	SDL_Delay(100);
}


/* PRIVATE METHODS */


void
GUI::handleEvents(void)
{
	switch(event->type) {
		case SDL_QUIT:
			term_signal = true;
			break;
		default:
			break;
	}
}

