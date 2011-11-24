#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_

/* We may read files up to 64 KiB of size. That should be fairly enough:
 */
#define FILE_BUFFER 65535

// Utils:
#include <utils/ayestring.h>
#include <utils/exception.h>

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
		int getID(char const* name);
		int getHighestID(void);
	
		/* GETTERS */
		size_t getName(char* buffer, int id, size_t len);
		size_t getEffect(char* buffer, int id, size_t len);
		size_t getTrigger(char* buffer, int id, size_t len);
		size_t getRules(char* buffer, int id, size_t len);
		int getValue(int id);
		int getLevel(int id);
		int getTribe(int id);
		int getUser(int id);
		size_t getInventory(std::vector<int>* buffer, int id);

		/* SETTERS */
		bool setName(char const* name, int id);
		bool setValue(int value, int id);
		bool setLevel(int level, int id);
		bool setTribe(int tribe, int id);
		bool setUser(int user_id, int id);
		bool setInventory(const std::vector<int>* inventory, int id);
		int addCharacter(void);
	
	private:
		size_t updateEntry(int id);
		size_t tokenize(char const* key, int id);

		std::vector<char*> file_buffer;
		std::vector<char*> entry_buffer;
		std::vector<char*> line_buffer; // tokenized
		char* path;
		int id;
};

#endif

