#ifndef _SESSION_H_
#define _SESSION_H_

#include "user.h"
#include "pipe.h"

#include <utils/ayelog.h>

#include <cstring>

class
Session
{
	public:
		Session(int session_id, char const* ip, Pipe* pipe);
		~Session(void);
		void process(char const* message, size_t message_len);
		char const* getIP(void);
		int getSessionID(void);
	
	private:
		Pipe* pipe;
		int session_id;
		char* ip;
		bool authenticated;
		int user_id;
		bool logged_in;
		int character_id;
};

#endif

