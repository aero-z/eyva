#ifndef _REGION_H_
#define _REGION_H_

#include "object.h"
#include "character.h"

#include <vector>

#define REGION_WIDTH 40
#define REGION_HEIGHT 20

class
Region
{
	public:
		Region(void);
		~Region(void);
		bool addObject(Object* object, int x, int y);
		bool removeObject(Object*);
		bool removeObject(int x, int y);
	
	private:
		std::vector<Character*> characters;
		int terrain[REGION_WIDTH][REGION_HEIGHT];
		Object* objects[REGION_WIDTH][REGION_HEIGHT];
};

#endif

