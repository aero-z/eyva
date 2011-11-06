#ifndef _USER_H_
#define _USER_H_

#include <cstring>  // for name handling

class
User
{
	public:
		User(int id);
		~User(void);
		size_t getName(char* name);
		int getID(void);
	
	private:
		char* name;
		int id;
};

#endif

