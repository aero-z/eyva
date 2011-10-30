#ifndef _USER_H_
#define _USER_H_

#include <cstring>   // for strcpy name

class User {
	public:
		User(char const* name);
		~User(void);
		char const* getName();
	
	private:
		char* name;
};

#endif
