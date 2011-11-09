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
		Session(int id, char const* ip, Pipe* pipe);
		~Session(void);
		void handle(char const* message, int message_len);
		char const* getIP(void);
		int getID(void);
	
	private:
		Pipe* pipe;
		int id;
		char* ip;
};

#endif

