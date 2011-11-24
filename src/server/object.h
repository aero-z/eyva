#ifndef _OBJECT_H_
#define _OBJECT_H_

// Utils:
#include <utils/file_handler.h>
#include <utils/exception.h>

class
Object
{
	public:
		Object(int id, FileHandler* file_handler);
		~Object(void);

	private:
		FileHandler* file_handler;
		int id;
		char* name;
		char* rules;
		char* effect;
		char* trigger;
		int value;
};

#endif

