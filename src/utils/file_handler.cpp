#include "file_handler.h"

/**
 * Constructor.
 * Gets the content of a given file.
 * @param path  The path to the file that shall be "dumped".
 */
FileHandler::FileHandler(char const* path)
{
	this->path = new char[strlen(path)+1];
	strcpy(this->path, path);

	file_buffer.clear();
	char content_buffer[FILE_BUFFER];
	id = 0;

	/* If the file does not exist or could not be read, break here:
	 */
	FILE* file;
	if((file = fopen(path, "r")) == NULL) {
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
 * @param path   The path of the file that shall be searched.
 * @param id     The ID of the entry.
 * @return       The length of the name. 0 if the name could not be found.
 */
size_t
FileHandler::getName(char* buffer, int id)
{
	if(this->id != id) {
		this->id = id;
		updateEntry();
	}

	/* Get the "name" entry:
	 */
	for(size_t line = 0; line < entry_buffer.size(); line++) {
		if(strncmp(entry_buffer[line], "name|", 5) == 0) {
			strcpy(buffer, entry_buffer[line]+5);
			return strlen(buffer);
		}
	}

	return 0;
}

/**
 * This method gets the "effect" field of a given ID from a given file.
 * @param buffer The buffer where the effect message shall be written to.
 * @param path   The path of the file that shall be searched.
 * @param id     The ID of the entry.
 * @return       The length of the message.
 */
size_t
FileHandler::getEffect(char* buffer, int id)
{
	// TODO
	return 0;
}

/**
 * This method gets the "trigger" field of a given ID from a given file.
 * @param buffer The buffer where the triggering message shall be written to.
 * @param path   The path of the file that shall be searched.
 * @param id     The ID of the entry.
 * @return       The length of the message.
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
 * @param path   The path of the file that shall be searched.
 * @param id     The ID of the entry.
 * @return       The length of the message.
 */
size_t
FileHandler::getDescription(char* buffer, int id)
{
	// TODO
	return 0;
}

/**
 * This method gets the "value" field of a given ID from a given file.
 * @param path The path of the file that shall be searched.
 * @param id   The ID of the entry.
 * @return     The value of the "value" field.
 */
int
FileHandler::getValue(int id)
{
	// TODO
	return 0;
}

/**
 * This method gets the "level" field of a given ID from a given file.
 * @param path The path of the file that shall be searched.
 * @param id   The ID of the entry.
 * @return     The value of the "level" field.
 */
int
FileHandler::getLevel(int id)
{
	// TODO
	return 0;
}

/**
 * This method gets the entries at the "inventory" field of a given ID from a
 * given file.
 * @param buffer The buffer where the object IDs shall be stored to.
 * @param path   The path to the file that shall be searched.
 * @param id     The ID of the entry.
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
 * @param path   The path to the file that shall be searched.
 * @param id     The ID of the entry.
 */
size_t
FileHandler::getCharacters(std::vector<int>* buffer, int id)
{
	// TODO
	return 0;
}

/**
 * This method gets the "tribe" field of a given ID from a given file.
 * @param path The path of the file that shall be searched.
 * @param id   The ID of the entry.
 * @return     The value of the "tribe" field.
 */
int
FileHandler::getTribe(int id)
{
	// TODO
	return false;
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

bool
FileHandler::setTribe(int tribe, int id)
{
	// TODO
	return false;
}


/* PRIVATE METHODS */


/**
 * This method copies all lines of the entry defined by the "id" value to the
 * entry buffer.
 * @return The number of lines copied, 0 if the entry has not been found.
 */
size_t
FileHandler::updateEntry(void)
{
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
				if(strstr(file_buffer[i], "id|") == file_buffer[i]
						&& aton(file_buffer[i]+3, 10) == id) {
					entry_buffer.clear();
					for(size_t j = entry_start+1; j < entry_end; j++)
						entry_buffer.push_back(file_buffer[j]);
					found = true;
					break;
				}
			}
		}
	}
	return found ? entry_buffer.size() : 0;
}

