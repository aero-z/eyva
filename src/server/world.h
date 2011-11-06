#ifndef _WORLD_H_
#define _WORLD_H_

#include "region.h"
#include "object.h"
#include "character.h"

#include <vector>

/* How many layers of regions there are:
 */
#define WORLD_LAYERS 1

/* How many regions there are from east to west:
 */
#define WORLD_WIDTH 1

/* How many regions there are from north to south:
 */
#define WORLD_HEIGHT 1

class
World
{
	public:
		World(void);
		~World(void);
	
	private:
		Region* regions[WORLD_LAYERS][WORLD_WIDTH][WORLD_HEIGHT];
		void createObjects(void);
		void createCharacters(void);
};

#endif

