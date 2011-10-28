#ifndef _DATA_GUARD_H_
#define _DATA_GUARD_H_

#include "user.h"

#include <vector>     // for the list of connected users

class DataGuard {
	public:
		DataGuard();
		void process(char *, char const *, int);
	
	private:
		std::vector<User *> users;
};

#endif
