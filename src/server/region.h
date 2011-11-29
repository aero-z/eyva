/*
* `eyva' (server) - Region data handler.
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

#ifndef _REGION_H_
#define _REGION_H_

// Server:
#include "character.h"

// Other:
#include <vector>

class
Region
{
	public:
		Region();
		~Region();
		void addCharacter(Character* character);
	
	private:
		std::vector<Character*> characters;
		char terrain[40][20];
};

#endif

