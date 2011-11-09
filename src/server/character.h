#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "object.h"
 
#include <vector>
#include <cstring>

class
Character
{
	public:
		Character(int id);
		~Character(void);
		size_t getName(char* name);
		int getXPos(void);
		int getYPos(void);
		void setXPos(int xpos);
		void setYPos(int ypos);

	private:
		std::vector<Object*> objects;
		int id;
		char* name;
		int xpos;
		int ypos;
};

#endif

