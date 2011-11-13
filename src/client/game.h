#ifndef _GAME_H_
#define _GAME_H_

#include "region.h"

class
Game
{
	public:
		Game(void);
		~Game(void);
		void process(char const* msg);

	private:
		Region* region;
};

#endif

