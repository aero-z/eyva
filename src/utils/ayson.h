#ifndef _AYSON_H_
#define _AYSON_H_

#include <vector>

/**
 * This class is responsible for reading data out of and writing data to
 * savefiles in the `Ayson' format.
 */
class
Ayson
{
	public:
		/* These methods are here to read from savefiles:
		 */
		static size_t
		getName(char* buffer, char const* filename, unsigned int id);

		static size_t
		getEffect(char* buffer, char const* filename, unsigned int id);

		static size_t
		getDescription(char* buffer, char const* filename, unsigned int id);

		static unsigned int
		getValue(char const* filename, unsigned int id);

		static unsigned int
		getLevel(char const* filename, unsigned int id);

		static bool
		getInventory(std::vector<int> buffer, char const* filename,
				unsigned int id);

		static bool
		getCharacters(std::vector<int> buffer, char const* filename,
				unsigned int id);

		static unsigned int
		getTribe(char const* filename, unsigned int id);

		/* These methods are here to write to savefiles:
		 */
		static bool
		setName(char const* filename, char const* name, unsigned int id);

		static bool
		setValue(char const* filename, unsigned int value, unsigned int id);

		static bool
		setLevel(char const* filename, unsigned int level, unsigned int id);

		static bool
		setInventory(char const* filename, std::vector<int> inventory,
				unsigned int id);

		static bool
		setCharacters(char const* filename, std::vector<int> characters,
				unsigned int id);

		static bool
		addCharacter(char const* filename);

		static bool
		setTribe(char const* filename, unsigned int tribe, unsigned int id);
};

#endif

