#ifndef _DATA_GUARD_H_
#define _DATA_GUARD_H_

#include "user.h"
#include <eyva.h>

#include <vector>     // for the list of connected users

class DataGuard {
	public:
		DataGuard(void);
		void process(char* buffer_out, char const* buffer_in);
	
	private:
		std::vector<User*> users;
};

#endif
