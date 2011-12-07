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

#include "savefile.h"

using namespace AyeString;

/**
 * Constructor.
 * Gets the content of a given file.
 * @param path The path to the file that shall be read.
 */
Savefile::Savefile(char const* path)
{
	this->path = new char[strlen(path)+1]; // +1 for \0
	strcpy(this->path, path);

	char content_buffer[FILE_SIZE];
	id = 0;

	/* If the file does not exist or could not be read, break here:
	 */
	FILE* file;
	if((file = fopen(path, "r")) == NULL)
		throw new Exception("could not open file: %s", path);
	
	/* Otherwise, start copying the whole file content to the temporary buffer:
	 */
	int filesize;
	for(filesize = 0; filesize < FILE_SIZE; filesize++) {
		content_buffer[filesize] = fgetc(file);

		/* If the end of file was reached, replace it by a terminating \0 and
		 * quit copying:
		 */
		if(content_buffer[filesize] == EOF) {
			content_buffer[filesize] = 0;
			break;
		}
	}
	fclose(file);

	/* Copy line per line to the buffer:
	 */
	unsigned int line_begin = 0;
	for(int i = 0; i < filesize; i++) {
		/* If the current character is a newline, copy everything from the
		 * beginning of the line to the current character - 1 (without newline)
		 * to a newly created C string:
		 */
		if(content_buffer[i] == 10) {
			int line_size = i-line_begin; // without \n
			char* line = new char[line_size+1]; // +1 for \0
			strncpy(line, content_buffer+line_begin, line_size);
			line[line_size] = 0; // terminate
			file_buffer.push_back(line);
			line_begin = i+1; // update for next line
		}
	}

	/* Update the id_max variable that holds the value of the highest among IDs:
	 */
	updateIDMax();
}

/**
 * Destructor.
 */
Savefile::~Savefile(void)
{
	save();
}


/* PUBLIC METHODS */


/**
 * This method writes the buffer to the file.
 */
void
Savefile::save(void)
{
	// TODO
}

/**
 * This method gets the user ID to the provided name.
 * @param name The username for which the ID shall be returned.
 * @return     The ID according to the name.
 */
int
Savefile::getUserID(char const* name)
{
	/* Go through all entries and check if the name corresponds to the provided
	 * one:
	 */
	for(int id = 1; id <= id_max; id++) {
		tokenize("name", id);
		
		/* If it does, return the according ID; it's the searched one.
		 * Notice that we check with ignoring the preceding and tailing quote in
		 * the savefile value:
		 */
		if(line_buffer.size() > 1 && strncmp(line_buffer[1]+1, name,
				strlen(line_buffer[1]+1)-1) == 0) {
			return id;
		}
	}
	return 0;
}

/**
 * This method gets a string value to a specified key.
 * @param buffer The buffer where the string shall be written to.
 * @param id     The ID of the entry.
 * @param key    The key of the entry.
 * @param len    The buffer length.
 * @return       The length of the string (may be larger than the copied length
 *               if the buffer was too small). 0 if not found.
 */
size_t
Savefile::getString(char* buffer, int id, char const* key, size_t len)
{
	if(key != NULL && tokenize(key, id) > 1) {
		if(buffer != NULL) {
			memcpy(buffer, line_buffer[1]+1, len); // skip preceding quote
			buffer[strlen(line_buffer[1])-2] = 0; // replace tailing quote by \0
		}
		return strlen(line_buffer[1])-2;
	}
	return 0;
}

/**
 * This method gets a numeric value to a specified key.
 * @param id  The ID of the entry.
 * @param key The key of the entry.
 * @return    The value of the field. 0 if not found.
 */
int
Savefile::getValue(int id, char const* key)
{
	if(key != NULL && tokenize(key, id) > 1) {
		return aton(line_buffer[1], 10);
	}
	return 0;
}

/**
 * This method gets a list of numeric values to a specified key.
 * @param buffer The vector where the list of values shall be stored to.
 * @param id     The ID of the entry.
 * @param key    The key of the entry.
 * @return       The number of values found. 0 if not found.
 */
size_t
Savefile::getList(std::vector<int>* buffer, int id, char const* key)
{
	if(key != NULL && tokenize(key, id) > 1) {
		if(buffer != NULL) {
			buffer->clear();
			for(size_t i = 1; i < line_buffer.size(); i++)
				buffer->push_back(aton(line_buffer[i], 10));
		}
		return line_buffer.size()-1; // -1 for key
	}
	return 0;
}

bool
Savefile::setString(int id, char const* key, char const* string)
{
	// TODO
	return false;
}

bool
Savefile::setValue(int id, char const* key, int value)
{
	// TODO
	return false;
}

bool
Savefile::setList(int id, char const* key, std::vector<int>* list)
{
	// TODO
	return false;
}

/**
 * This method creates a new entry.
 * @return The new entry's ID.
 */
int
Savefile::addEntry(void)
{
	// TODO
	return 0;
}


/* PRIVATE METHODS */


/**
 * This method copies all lines of the entry defined by the "id" value to the
 * entry buffer.
 * @return The number of lines copied, 0 if the entry has not been found.
 */
size_t
Savefile::updateEntry(int id)
{
	/* If the requested ID is already loaded, don't continue here:
	 */
	if(this->id == id)
		return 0;
	
	bool found = false;
	size_t entry_start = 0, entry_end = 0;

	/* Go through all the lines in the file content buffer while nothing has
	 * been found:
	 */
	for(size_t file_line = 0; file_line < file_buffer.size() && !found;
			file_line++) {
		/* If an entry starts here, mark this line as the entry start:
		 */
		if(strcmp(file_buffer[file_line], "{") == 0)
			entry_start = file_line;

		/* If an entry ends here, mark this line as end and search every line
		 * from the start line to the end line for the "id" entry:
		 */
		if(strcmp(file_buffer[file_line], "}") == 0) {
			entry_end = file_line;

			for(size_t i = entry_start+1; i < entry_end; i++) {
				/* If the searched entry has been found, copy all lines in the
				 * entry's area to the entry buffer and set the "found" flag:
				 */
				if(strstr(file_buffer[i], "id:") == file_buffer[i]
						&& aton(file_buffer[i]+3, 10) == id) {
					entry_buffer.clear();
					for(size_t j = entry_start+1; j < entry_end; j++) {
						/* Basically the entry buffer points to the same values
						 * as the file buffer, so whenever the entry buffer is
						 * modified, the file buffer will be too.
						 * This reduces the amount of memory used and erases the
						 * necessity to "store" values back to the file buffer.
						 *
						 * And it's easier.
						 */
						entry_buffer.push_back(file_buffer[j]);
					}
					found = true;
					break;
				}
			}
		}
	}

	if(found) {
		this->id = id;
		return entry_buffer.size();
	}

	return 0;
}

/**
 * This method splits up a line into its tokens according to the Ayson format.
 * @param key The key to the line that is wished to be tokenized.
 * @param id  The entry's ID.
 * @return    The number of tokens generated. 0 if not found.
 */
size_t
Savefile::tokenize(char const* key, int id)
{
	/* Update the content of the entry buffer to make sure we're handling the
	 * right data:
	 */
	updateEntry(id);

	/* Make a local copy of the key to be searched:
	 */
	char* tmp = new char[strlen(key)+2]; // +2 for ':' and \0
	strcpy(tmp, key);
	tmp[strlen(key)] = ':';
	tmp[strlen(key)+1] = 0;

	/* Determinate the correct line:
	 */
	bool found = false;
	size_t line;
	for(line = 0; line < entry_buffer.size(); line++) {
		if(strncmp(entry_buffer[line], tmp, strlen(tmp)) == 0) {
			found = true;
			break;
		}
	}
	delete[] tmp;

	if(!found)
		return 0;

	/* Start going through the characters of the line:
	 */
	line_buffer.clear();
	int start = 0;
	bool is_string = false;
	bool is_comment = false;
	/* Include the last character (\0), too, so we know when to stop (therefore
	 * <= instead of <):
	 */
	for(size_t i = 0; i <= strlen(entry_buffer[line]); i++) {
		/* If the ':' appears inside a string, we don't treat it as delimiter,
		 * so we need to toggle "string mode" at every occurence of '"':
		 */
		if(entry_buffer[line][i] == '"' && !is_comment)
			is_string = !is_string;

		/* If the '#' appears outside a string, it's a comment:
		 */
		if(entry_buffer[line][i] == '#' && !is_string)
			is_comment = true;

		/* If there's a delimiter or the end of the string, add all characters
		 * from the start to here to the tokens's list:
		 */
		if((entry_buffer[line][i] == ':' && !is_string && !is_comment)
				|| entry_buffer[line][i] == 0) {
			tmp = new char[i-start+1]; // +1 for \0
			strncpy(tmp, entry_buffer[line]+start, i-start);
			tmp[i-start] = 0; // terminate

			/* Don't add empty fields!
			 */
			if(strlen(tmp) > 0)
				line_buffer.push_back(tmp);

			start = i+1; // update start pointer
		}
	}

	return line_buffer.size();
}

/**
 * This method sets the id_max variable representing the highest among IDs.
 * TODO make it dynamic (without .max entry)
 */
void
Savefile::updateIDMax(void)
{
	/* Go through every line to check if the ".max" entry is here:
	 */
	for(size_t i = 0; i < file_buffer.size(); i++)
		/* If the entry is there, return the value behind:
		 */
		if(strncmp(file_buffer[i], ".max:", 5) == 0) {
			id_max = aton(file_buffer[i]+5, 10);
			return;
		}
	/* If the highest ID is not indicated, throw an exception to indicate that
	 * the file is corrupted:
	 */
	throw new Exception("%s corrupted: no `.max' entry found", path);
}

