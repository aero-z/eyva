/*
 * EYVA - savefile handler
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

#ifndef _SAVEFILE_H_
#define _SAVEFILE_H_

// files up to 64 KiB should be OK:
#define FILE_SIZE 65536

#include "utils/ayestring.h"
#include "utils/exception.h"

#include <vector>
#include <cstring>
#include <cstdio>

class
Savefile
{
	public:
		Savefile(char const* path);
		~Savefile(void);
		void save(void);
	
		int getUserID(char const* name);
		size_t getString(char* buffer, int id, char const* key, size_t len);
		int getValue(int id, char const* key);
		size_t getList(std::vector<int>* buffer, int id, char const* key);

		bool setString(int id, char const* key, char const* string);
		bool setValue(int id, char const* key, int value);
		bool setList(int id, char const* key, std::vector<int>* list);

		int addEntry(void);

	private:
		size_t updateEntry(int id);
		size_t tokenize(char const* key, int id);
		void updateIDMax(void);

		char* path;
		std::vector<char*> file_buffer;
		int id;
		std::vector<char*> entry_buffer;
		char* key;
		std::vector<char*> line_buffer;

		int id_max;
};

#endif

