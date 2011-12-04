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

GUI::GUI(void)
{
	pipe = new Pipe();
	network = NULL;

	// TODO
}

GUI::~GUI(void)
{
	delete pipe;
	if(network != NULL)
		delete network;
}


/* PUBLIC METHODS */


/**
 * Initiate the game loop.
 */
void
GUI::run(void)
{
	// TODO
}

