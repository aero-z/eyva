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

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

class
Character
{
	public:
		Character(int session_id, int character_id);
		~Character(void);
		int getSessionID(void);
		int getCharacterID(void);
		unsigned int getLevel(void);
		char const* getName(void);
	
	private:
		char* name;
		unsigned int session_id;
		unsigned int character_id;
		unsigned int level;
		unsigned int tribe;
		unsigned int value;
};

#endif

