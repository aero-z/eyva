#ifndef _SESSION_H_
#define _SESSION_H_

// Game:
#include "user.h"
#include "pipe.h"
#include "game.h"

// Hybrid:
#include <hybrid/eyva.h>

// Utils:
#include <utils/ayelog.h>

// Others:
#include <cstring>

class
Session
{
	public:
		Session(int session_id, char const* ip, Pipe* pipe, Game* game);
		~Session(void);
		void process(char const* message, size_t message_len);
		char const* getIP(void);
		int getSessionID(void);
	
	private:
		Pipe* pipe;
		Game* game;
		User* user;
		int session_id;
		char* ip;
		int user_id;
		bool authenticated;
		char buffer[BUFFER_SIZE];
};

#endif

