#ifndef _AYSON_H_
#define _AYSON_H_

/* We may read files up to 16 MiB of size. That should be fairly enough:
 */
#define FILE_BUFFER 16777216

#include <vector>
#include <cstring>
#include <cstdio>

/**
 * This class is responsible for reading data out of and writing data to
 * savefiles in the `Ayson' format.
 */
class
Ayson
{
	public:
		static size_t getFileLines(std::vector<char*>* buffer,
				char const* path);
	
		/* GETTERS */
		static size_t
			getName(char* buffer, char const* path, unsigned int id);
		static size_t
			getEffect(char* buffer, char const* path, unsigned int id);
		static size_t
			getTrigger(char* buffer, char const* path, unsigned int id);
		static size_t
			getDescription(char* buffer, char const* path, unsigned int id);
		static unsigned int
			getValue(char const* path, unsigned int id);
		static unsigned int
			getLevel(char const* path, unsigned int id);
		static size_t
			getInventory(std::vector<int>* buffer, char const* path,
					unsigned int id);
		static size_t
			getCharacters(std::vector<int>* buffer, char const* path,
					unsigned int id);
		static unsigned int
			getTribe(char const* path, unsigned int id);

		/* SETTERS */
		static bool
			setName(char const* path, char const* name, unsigned int id);
		static bool
			setValue(char const* path, unsigned int value, unsigned int id);
		static bool
			setLevel(char const* path, unsigned int level, unsigned int id);
		static bool
			setInventory(char const* path, const std::vector<int>* inventory,
					unsigned int id);
		static bool
			setCharacters(char const* path, const std::vector<int>* characters,
					unsigned int id);
		static bool
			addCharacter(char const* path);
		static bool
			setTribe(char const* path, unsigned int tribe, unsigned int id);
};

#endif

