#ifndef _GAME_H_
#define _GAME_H_

#include "data_handler.h"

class Game {
	public:
		Game(DataHandler* data_handler);
		~Game(void);
		void poll(void);
	
	private:
		DataHandler* data_handler;
		char command[BUFFER_SIZE];
		size_t command_len;
};

#endif

