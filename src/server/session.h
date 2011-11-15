#ifndef _SESSION_H_
#define _SESSION_H_

#include "user.h"
#include "pipe.h"
#include "game.h"

#include <utils/ayelog.h>

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
		bool authenticated;
		int user_id;
		bool logged_in;
		int character_id;
};

#endif

