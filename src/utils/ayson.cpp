#include "ayson.h"

/**
 * This is probably the most generic method of this class.
 * It opens a file and writes each line to a given buffer.
 * @param buffer The buffer where the file content shall be written to. Each
 *               element of the buffer vector corresponds to a line in the file.
 * @param path   The path to the file that shall be "dumped".
 * @return       The number of lines read.
 */
size_t
Ayson::getFileLines(std::vector<char*>* buffer, char const* path)
{
	char content_buffer[FILE_BUFFER];

	/* If the file does not exist or could not be read, break here:
	 */
	FILE* file;
	if((file = fopen(path, "r")) == NULL)
		return 0;
	
	/* Otherwise, start copying the whole file content to the temporary buffer,
	 * and count:
	 */
	size_t filesize = 0;
	while(!feof(file)) {
		fgets(content_buffer, FILE_BUFFER, file);
		filesize++;
	}
	fclose(file);

	/* Copy line per line to the buffer:
	 */
	unsigned int line_start = 0;
	for(size_t i = 0; i < filesize; i++) {
		/* If the current character is a newline, copy everything from the
		 * beginning of the line to the current character - 1 (without newline)
		 * to a newly created C string:
		 */
		if(content_buffer[i] == 10) {
			char* line = new char[i-line_start]; // -1 for \n; +1 for \0
			memcpy(line, content_buffer+line_start, i-line_start-1);
			line[i] = 0; // terminate
			buffer->push_back(line);
			line_start = i+1; // update for next line
		}
	}

	return buffer->size();
}


/* GETTERS */


/**
 * This method gets the "name" field of a given ID from a given file.
 * @param buffer The buffer where the name shall be written to.
 * @param path   The path of the file that shall be searched.
 * @param id     The ID of the entry.
 * @return       The length of the name.
 */
size_t
Ayson::getName(char* buffer, char const* path, unsigned int id)
{
	// TODO
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
Ayson::getEffect(char* buffer, char const* path, unsigned int id)
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
Ayson::getTrigger(char* buffer, char const* path, unsigned int id)
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
Ayson::getDescription(char* buffer, char const* path, unsigned int id)
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
unsigned int
Ayson::getValue(char const* path, unsigned int id)
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
unsigned int
Ayson::getLevel(char const* path, unsigned int id)
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
Ayson::getInventory(std::vector<int>* buffer, char const* path, unsigned int id)
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
Ayson::getCharacters(std::vector<int>* buffer, char const* path,
		unsigned int id)
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
unsigned int
Ayson::getTribe(char const* path, unsigned int id)
{
	// TODO
	return false;
}


/* SETTERS */


bool
Ayson::setName(char const* path, char const* name, unsigned int id)
{
	// TODO
	return false;
}

bool
Ayson::setValue(char const* path, unsigned int value, unsigned int id)
{
	// TODO
	return false;
}

bool
Ayson::setLevel(char const* path, unsigned int level, unsigned int id)
{
	// TODO
	return false;
}

bool
Ayson::setInventory(char const* path, const std::vector<int>* inventory,
		unsigned int id)
{
	// TODO
	return false;
}

bool
Ayson::setCharacters(char const* path, const std::vector<int>* characters,
		unsigned int id)
{
	// TODO
	return false;
}

bool
Ayson::addCharacter(char const* path)
{
	// TODO
	return false;
}

bool
Ayson::setTribe(char const* path, unsigned int tribe, unsigned int id)
{
	// TODO
	return false;
}

