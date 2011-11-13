#ifndef _NETWORK_H_
#define _NETWORK_H_

// Server side headers:
#include "session.h"
#include "game.h"
#include "pipe.h"

// Non-specific headers:
#include <hybrid/eyva.h> 

// Utilities:
#include <utils/ayelog.h>
#include <utils/exception.h>
#include <utils/ayestring.h>

// Network headers:
#include <sys/types.h>  // socket types
#include <sys/socket.h> // sockets
#include <arpa/inet.h>  // inet (3) functions
#include <unistd.h>     // for write, read
#include <cerrno>       // for the "errno" macro

// Others:
#include <cstring>
#include <vector>
#include <map>
#include <utility>

/* Number of sessions that this server can handle:
 */ 
#define SESSIONS_MAX 10

/* Number of connection requests this server can keep in a queue:
 */
#define QUEUE_SIZE 3

class
Network
{
	public:
		Network(int port);
		~Network(void);
		void poll(void);

	private:
		void pollIn(void);
		void handleConnection(void);
		void handleData(int id);
		void pollOut(void);

		Game* game;
		Pipe* pipe;
		std::map<int, Session*> sessions;
		std::map<int, Session*>::iterator it; // iterator for the sessions map
		int sockc;                            // connection socket
		char buffer_in[BUFFER_SIZE];
		char buffer_out[BUFFER_SIZE];
};

#endif

