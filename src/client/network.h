#ifndef _NETWORK_H_
#define _NETWORK_H_

// Client:
#include "pipe.h"
#include "ui/ui.h"
#include "game.h"

// Utils:
#include <utils/ayelog.h>
#include <utils/exception.h>

// Hybrid:
#include <hybrid/eyva.h>

// Network:
#include <sys/types.h>   // socket types
#include <sys/socket.h>  // sockets
#include <arpa/inet.h>   // inet (3) functions
#include <unistd.h>      // for write, read
#include <fcntl.h>       // for non-blocking socket

// Others:
#include <cerrno>
#include <cstring>

class
Network
{
	public:
		Network(Game* game, UI* ui, Pipe* pipe);
		~Network(void);
		void poll(void);

	private:
		bool connect(char const* ip, int port);
		void disconnect(void);
		void pollIn(void);
		void pollOut(void);

		Game* game;
		UI* ui;
		Pipe* pipe;
		int sockc;
		char buffer_in[BUFFER_SIZE];
		char buffer_out[BUFFER_SIZE];
		bool connected;
};

#endif

