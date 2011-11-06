#ifndef _GAME_H_
#define _GAME_H_

#include "data_handler.h"
#include "client.h"
#include <vector>

class
Game
{
	public:
		Game(DataHandler* data_handler);
		~Game(void);
		void poll(void);
	
	private:
		DataHandler* data_handler;
		char effect[BUFFER_SIZE];
		size_t effect_len;
};

#endif

