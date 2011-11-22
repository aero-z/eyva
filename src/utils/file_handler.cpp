#include "file_handler.h"

/**
 * Constructor.
 * Gets the content of a given file.
 * @param path  The path to the file that shall be "dumped".
 */
FileHandler::FileHandler(char const* path, bool* flag)
{
	this->path = new char[strlen(path)+1];
	strcpy(this->path, path);
	*flag = true; // assume everything is alright

	file_buffer.clear();
	char content_buffer[FILE_BUFFER];
	id = 0;

	/* If the file does not exist or could not be read, break here:
	 */
	FILE* file;
	if((file = fopen(path, "r")) == NULL) {
		*flag = false;
		return;
	}
	
	/* Otherwise, start copying the whole file content to the temporary buffer:
	 */
	int filesize;
	for(filesize = 0; filesize < FILE_BUFFER; filesize++) {
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
}

/**
 * Destructor.
 */
FileHandler::~FileHandler(void)
{
	save();
}

/**
 * This method writes the buffer to the file.
 */
void
FileHandler::save(void)
{
	// TODO
}


/* PUBLIC METHODS */


/* GETTERS */


/**
 * This method gets the "name" field of a given ID from a given file.
 * @param buffer The buffer where the name shall be written to.
 * @param id     The ID of the entry.
 * @return       The length of the name. 0 if not found.
 */
size_t
FileHandler::getName(char* buffer, int id)
{
	/* Tokenize the line with the "name" keyword:
	 */
	if(tokenize("name", id) > 1) {
		strcpy(buffer, line_buffer[1]);
		return strlen(buffer);
	} else
		return 0;
}

/**
 * This method gets the "effect" field of a given ID from a given file.
 * @param buffer The buffer where the effect message shall be written to.
 * @param id     The ID of the entry.
 * @return       The length of the message. 0 if not found.
 */
size_t
FileHandler::getEffect(char* buffer, int id)
{
	updateEntry(id);

	// TODO
	return 0;
}

/**
 * This method gets the "trigger" field of a given ID from a given file.
 * @param buffer The buffer where the triggering message shall be written to.
 * @param id     The ID of the entry.
 * @return       The length of the message. 0 if not found.
 */
size_t
FileHandler::getTrigger(char* buffer, int id)
{
	// TODO
	return 0;
}

/**
 * This method gets the "description" field of a given ID from a given file.
 * @param buffer The buffer where the description shall be written to.
 * @param id     The ID of the entry.
 * @return       The length of the description. 0 if not found.
 */
size_t
FileHandler::getDescription(char* buffer, int id)
{
	// TODO
	return 0;
}

/**
 * This method gets the "value" field of a given ID from a given file.
 * @param id   The ID of the entry.
 * @return     The value of the "value" field. 0 if not found.
 */
int
FileHandler::getValue(int id)
{
	// TODO
	return 0;
}

/**
 * This method gets the "level" field of a given ID from a given file.
 * @param id   The ID of the entry.
 * @return     The value of the "level" field. 0 if not found.
 */
int
FileHandler::getLevel(int id)
{
	// TODO
	return 0;
}

/**
 * This method gets the "tribe" field of a given ID from a given file.
 * @param id   The ID of the entry.
 * @return     The value of the "tribe" field. 0 if not found.
 */
int
FileHandler::getTribe(int id)
{
	// TODO
	return false;
}

/**
 * This method gets the entries at the "inventory" field of a given ID from a
 * given file.
 * @param buffer The buffer where the object IDs shall be stored to.
 * @param id     The ID of the entry.
 * @return       The number of objects. 0 if not found.
 */
size_t
FileHandler::getInventory(std::vector<int>* buffer, int id)
{
	// TODO
	return 0;
}

/**
 * This method gets the entries at the "characters" field of a given ID from a
 * given file.
 * @param buffer The buffer where the character IDs shall be stored to.
 * @param id     The ID of the entry.
 * @return       The number of characters. 0 if not found.
 */
size_t
FileHandler::getCharacters(std::vector<int>* buffer, int id)
{
	// TODO
	return 0;
}


/* SETTERS */


bool
FileHandler::setName(char const* name, int id)
{
	// TODO
	return false;
}

bool
FileHandler::setValue(int value, int id)
{
	// TODO
	return false;
}

bool
FileHandler::setLevel(int level, int id)
{
	// TODO
	return false;
}

bool
FileHandler::setTribe(int tribe, int id)
{
	// TODO
	return false;
}

bool
FileHandler::setInventory(const std::vector<int>* inventory,
		int id)
{
	// TODO
	return false;
}

bool
FileHandler::setCharacters(const std::vector<int>* characters,
		int id)
{
	// TODO
	return false;
}

int
FileHandler::addCharacter(void)
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
FileHandler::updateEntry(int id)
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
		if(strcmp(file_buffer[file_line], ".start") == 0) {
			entry_start = file_line;
		}

		/* If an entry ends here, mark this line as end and search every line
		 * from the start line to the end line for the "id" entry:
		 */
		if(strcmp(file_buffer[file_line], ".end") == 0) {
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
	} else
		return 0;
}

/**
 * This method splits up a line into its tokens according to the Ayson format.
 * @param key The key to the line that is wished to be tokenized.
 * @param id  The entry's ID.
 * @return    The number of tokens generated. 0 if not found.
 */
size_t
FileHandler::tokenize(char const* key, int id)
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
		if(strstr(entry_buffer[line], tmp) == entry_buffer[line]) {
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
	 * >= instead of >):
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

