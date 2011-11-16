#ifndef _GAME_H_
#define _GAME_H_

#include "character.h"
#include "pipe.h"

class
Game
{
	public:
		Game(Pipe* pipe);
		~Game(void);
		void process(char const* msg);
		void logout(int session_id);
	
	private:
		Pipe* pipe;
		std::vector<Character*> characters;
};

#endif

