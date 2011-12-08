/*
 * `eyva'
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

#include "user.h"

/**
 * Constructor.
 * @param name The user's name that will be used to get the necessary
 * information from the users' savefile.
 */
User::User(char const* name, Savefile* savefile)
{
	this->savefile = savefile;

	/* Get the ID according to the name:
	 */
	printf("determinating ID ...\n");
	if((id = savefile->getUserID(name)) == 0)
		throw new Exception("no user named '%s'", name);
	
	/* If the user exists, generate the data:
	 */
	this->name = new char[strlen(name)+1]; // +1 for \0
	strcpy(this->name, name);
}

/**
 * Destructor.
 */
User::~User(void)
{
	// TODO update savefile
	delete name;
}


/* PUBLIC METHODS */


/**
 * This method provides the user's name.
 * @param name A pointer to the string where the name shall be written to.
 * @param len  The number of characters to be written (buffer size).
 * @return     The number of characters written.
 */
size_t
User::getName(char* name, size_t len)
{
	strncpy(name, this->name, len);
	return strlen(this->name);
}

/**
 * @return The users's ID.
 */
int
User::getID(void)
{
	return id;
}

