#ifndef _USER_H_
#define _USER_H_

#include <cstring>   // for strcpy name

class User {
	public:
		User(char const*);
		~User();
		char const* getName();
	
	private:
		char* name;
};

#endif
