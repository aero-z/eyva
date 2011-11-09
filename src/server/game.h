#ifndef _GAME_H_
#define _GAME_H_

#include "pipe.h"

class
Game
{
	public:
		Game(Pipe* pipe);
		~Game(void);
		void process(char const* msg);
	
	private:
		Pipe* pipe;
};

#endif

