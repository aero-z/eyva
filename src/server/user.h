#ifndef _USER_H_
#define _USER_H_

// Utils:
#include <utils/file_handler.h>
#include <utils/exception.h>

// Others:
#include <cstring>

class
User
{
	public:
		User(char const* name, FileHandler* file_handler);
		~User(void);
		size_t getName(char* name, size_t len);
		int getID(void);
	
	private:
		FileHandler* file_handler;
		char* name;
		int id;
};

#endif

