#ifndef _SESSION_H_
#define _SESSION_H_

#include "user.h"
#include "pipe.h"

#include <cstring>

class
Session
{
	public:
		Session(int id, char const* ip, Pipe* pipe);
		~Session(void);
		void handle(char const* message, int message_len);
	
	private:
		Pipe* pipe;
		int socket;
		char* ip;
};

#endif

