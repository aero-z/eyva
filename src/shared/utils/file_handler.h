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

#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_

/* We may read files up to 64 KiB of size. That should be fairly enough:
 */
#define FILE_SIZE 65536

// Utils:
#include "ayestring.h"
#include "exception.h"

// Others:
#include <vector>
#include <cstring>
#include <cstdio>

/**
 * This class is responsible for reading data out of and writing data to
 * savefiles in the `Ayson' format.
 */
class
FileHandler
{
	public:
		FileHandler(char const* path);
		~FileHandler(void);
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

