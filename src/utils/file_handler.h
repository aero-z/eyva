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
FileHandler
{
	public:
		FileHandler(size_t* size, char const* path);
		~FileHandler(void);
		void save(void);
	
		/* GETTERS */
		size_t getName(char* buffer, char const* path, unsigned int id);
		size_t getEffect(char* buffer, char const* path, unsigned int id);
		size_t getTrigger(char* buffer, char const* path, unsigned int id);
		size_t getDescription(char* buffer, char const* path, unsigned int id);
		unsigned int getValue(char const* path, unsigned int id);
		unsigned int getLevel(char const* path, unsigned int id);
		size_t getInventory(std::vector<int>* buffer, char const* path,
					unsigned int id);
		size_t getCharacters(std::vector<int>* buffer, char const* path,
					unsigned int id);
		unsigned int getTribe(char const* path, unsigned int id);

		/* SETTERS */
		bool setName(char const* path, char const* name, unsigned int id);
		bool setValue(char const* path, unsigned int value, unsigned int id);
		bool setLevel(char const* path, unsigned int level, unsigned int id);
		bool setInventory(char const* path, const std::vector<int>* inventory,
					unsigned int id);
		bool setCharacters(char const* path, const std::vector<int>* characters,
					unsigned int id);
		bool addCharacter(char const* path);
		bool setTribe(char const* path, unsigned int tribe, unsigned int id);
	
	private:
		size_t updateEntry(void);

		std::vector<char*> file_buffer;
		std::vector<char*> entry_buffer;
		char* path;
		unsigned int id;
};

#endif

