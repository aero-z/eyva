/*
* `eyva' (server) - Region data handler (implementation).
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

#include "region.h"

/**
 * Constructor.
 */
Region::Region(void)
{
	/* Default: void terrain
	 */
	for(int x = 0; x < 40; x++)
		for(int y = 0; y < 20; y++)
			terrain[x][y] = 0;
}

/**
 * Destructor.
 */
Region::~Region(void)
{
	// TODO
}

