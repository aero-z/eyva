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

#ifndef _USER_H_
#define _USER_H_

// Utils:
#include <utils/file_handler.h>
#include <utils/exception.h>

// Others:
#include <cstring>

class
User
{
	public:
		User(char const* name, FileHandler* file_handler);
		~User(void);
		size_t getName(char* name, size_t len);
		int getID(void);
	
	private:
		FileHandler* file_handler;
		char* name;
		int id;
};

#endif

