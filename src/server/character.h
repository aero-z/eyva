#ifndef _CHARACTER_H_
#ifndef _CHARACTER_H_

#include "property.h"
 
#include <vector.h>

class Character {
	public:
		Character(char const* name);
		~Character(void);
		size_t getName(char* name);

	private:
		std::vector<Property*> properties;
		char* name;
};

#endif

