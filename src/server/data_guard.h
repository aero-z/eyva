#ifndef _DATA_GUARD_H_
#define _DATA_GUARD_H_

#include "user.h"
#include <eyva_constants.h>

#include <vector>     // for the list of connected users

class DataGuard {
	public:
		DataGuard();
		void process(char *, char const *);
	
	private:
		std::vector<User *> users;
};

#endif
