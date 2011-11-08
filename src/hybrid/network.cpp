#include "network.h"

using namespace AyeLog;

/**
 * Constructor.
 *
 * @param pm
 *  The postmaster object, that is used to communicate with other parts of the
 *  program.
 *
 * @param session (server only)
 *  The session handler that holds information about all connections and users.
 */
#ifdef __ESERVER
	Network::Network(Postmaster* pm, Session* session)
#else
	Network::Network(Postmaster* pm);
#endif
{
	#ifdef __ESERVER
		this->session = session;
	#endif
	this->pm = pm;
	confirmation_byte = 0;
}

/**
 * Destructor.
 * In server mode, all clients are correctly (savegame, logout) disconnected,
 * and the network connection is shut down.
 */
Network::~Network(void)
{
	logf(LOG_NORMAL, "network: received shutdown signal");

	#ifdef __ESERVER
		session->disconnectAll();
	#endif
}


/* PUBLIC METHODS */


/**
 * This method starts the network activity. Depending on what it was compiled
 * for, it will start as a server that listens for incoming connections on the
 * indicated TCP port, or as a client that connects to the server indicated by
 * the IP address and the TCP port.
 *
 * @param ip (client only)
 *  The server's IP address to connect to.
 *
 * @param port
 *  The TCP port to listen on (if server) or to connect to (if client).
 */
void
#ifdef __ESERVER
	start(int port)
#else
	start(char const* ip, int port)
#endif
{
	/* Create socket:
	 * AF_INET:     domain (ARPA, IPv4)
	 * SOCK_STREAM: type (stream socket)
	 * IPPROTO_TCP: protocol (TCP)
	 */
	sockc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sockl < 0)
		throw new Exception("socket() failed");

	/* Clear the server_addr struct, then fill with appropriate data:
	 */
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;        // use IPv4
	server_addr.sin_port = htons(port);      // port to listen/connect to
	#ifdef __ESERVER
		server_addr.sin_addr.s_addr=htonl(INADDR_ANY); // allow all connections
	#else
		server_addr.sin_addr.s_addr=inet_addr(ip);     // the server's address
	#endif

	/* Set up the rest depending on what the network is used for:
	 */
	#ifdef __ESERVER
		/* Bind socket to information contained by the struct that was just
		 * defined:
		 * sockl:       socket that should bind to the address
		 * server_addr: information as declared above
		 * addrlen:     size of the address struct
		 */
		if(bind(sockc, (sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
			throw new Exception("bind() failed: %s", strerror(errno));
		}

		/* Start socket (we will use it to listen, since this is a server):
		 * sockc:         socket that should start listening
		 * CLIENTS_MAX:   #connections to keep in queue and to listen to
		 */
		if(listen(sockc, CLIENTS_MAX) < 0) {
			throw new Exception("listen() failed: %s", strerror(errno));
		}

		logf(LOG_NORMAL, "Listening on port %d ...", port);
	#else
		/* Connect to a server according to the information in the struct that
		 * was just defined:
		 */
		if(connect(sockc, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
			throw new Exception("connect() failed: %s", strerror(errno));
		}

		logf(LOG_NORMAL, "Connected to %s:%d ...", ip, port);
	#endif
}

/**
 * This method checks the postmaster for new messages and the sockets for new
 * data.
 */
void
Network::poll(void)
{
	pollOut();
	pollIn();
}


/* PRIVATE METHODS */


/**
 * This method checks the sockets for data.
 * select() is used, that will block until there is data, so as long as there's
 * no data, the program will sleep here.
 */
void
Network::pollIn(void)
{
	/* Before adding all used sockets to the fd_set, clear it:
	 */
	FD_ZERO(&socket_set);

	/* First, add the connection socket:
	 */
	FD_SET(sockl, &socket_set);

	/* If we're in server mode, there's also a list of client sockets to listen
	 * on:
	 */
	#ifdef __ESERVER
		for(size_t i = 0; i < session->countUsers(); i++) {
			FD_SET(session->getUser(i)->getSocket(), &socket_set);
		}
	#endif

	/* select() checks every socket in the socket_set, if there's some data on
	 * it.
	 * This method blocks until there's anything, so as soon as select()
	 * returns, we should have things to do.
	 * If we're running in server mode however, select() won't block, but just
	 * poll for new data and then continue:
	 */
	int selected;
	#ifdef __ECLIENT
		select_timeout.tv_sec = 0;
		select_timeout.tv_usec = 0;
		selected = select(FD_SETSIZE, &socket_set, NULL, NULL, &select_timeout);
	#else
		selected = select(FD_SETSIZE, &socket_set, NULL, NULL, NULL);
	#endif

	/* select() should return -1 if something went wrong. If we're in server
	 * mode, this is not supposed to happen, so crash:
	 */
	#ifdef __ESERVER
		if(selected < 0)
			throw new Exception("select() failed");
	#endif

	if(selected >= 0) {
		/* If we haven't crashed yet, check the connection socket. In server
		 * mode, new connections are handled there; in client mode, data is
		 * handled there.
		 */
		if(FD_ISSET(sockc, &socket_set)) {
			#ifdef __ESERVER
				handleConnection();
			#else
				handleData(sockc);
			#endif
		}

		/* If in server mode, cycle through all user's client sockets to check
		 * if there is data:
		 */
		#ifdef __ESERVER
			int s;
			for(size_t i = 0; i < session->countUsers(); i++)
				if(FD_ISSET(s = session->getUser(i)->getSocket(), &socket_set))
					handleData(s);
		#endif
	}
}

/**
 * This method checks the postbox for (a) command(s) to be sent out.
 */
void
Network::pollOut(void)
{
	/* While the box contains messages (return value > 0), handle the messages:
	 */
	int sent;
	for(size_t message_len = pm->getMessage(buffer_out, BOX_NETWORK);
			message_len > 0; ) {
		/* If we're in client mode, just send the message through the connection
		 * socket, otherwise use the byte zero to determine which client shall
		 * receive the message:
		 */
		#ifdef __ECLIENT
			sent = send(sockc, buffer_out, message_len, MSG_NOSIGNAL);
		#else
			sent = send(buffer_out[0], buffer_out, message_len, MSG_NOSIGNAL);
		#endif

		/* If something went wrong, we'll crash if in client mode, or disconnect
		 * the client if in server mode:
		 */
		if(sent <= 0) {
			#ifndef __ESERVER
				/* TODO
				session->disconnect(buffer_out[0]);
				*/
			#else
				throw new Exception("send() failed");
			#endif
		}
	}
}

/**
 * This method is only used by server mode and handles incoming connections.
 */
#ifdef __ESERVER
void
Network::handleConnection(void)
{
	/* Accept the connection:
	 */
	int sock_new = accept(sockc, NULL, NULL);

	/* accept() should return -1 if something went wrong. Again, as we don't
	 * want to handle the error yet, crash!
	 */
	if(sock_new < 0)
		throw new Exception("accept() failed");

	/* Add the new user to the session handler. If the session handler is full,
	 * it will return false, and the socket is thus closed:
	 */
	if(!session->addUser(sock_new)) {
		logf(LOG_WARNING, "rejected connection: session handler full");
		close(sock_new);
	}
}
#endif

/**
 * This method handles incoming data from a client.
 * @param id The client's ID (which is also the position in the std::vector the
 *           client is stored in).
 */
void
Network::handleData(int socket)
{
	/* Read data to buffer:
	 */
	int received = read(clients[id]->getSocket(), buffer_in, BUFFER_SIZE);
	logf(LOG_DEBUG, "received %d bytes", received);

	/* read() should return the number of bytes received. If the number is
	 * negative, there was an error, and we'll crash:
	 */
	if(received < 0)
		throw new Exception("read() failed");

	/* If the number of bytes received is equal to zero, the connection has been
	 * closed by the peer:
	 */
	if(received == 0) {
		logf(LOG_NORMAL, "> %s: connection closed by peer",
				clients[id]->getIP());
		removeClient(id);
	}

	/* If the number is positive, we have successfully received data:
	 */
	else {
		/* First, we send a confirmation message, the purpose of which being:
		 * 1) confirmation for server: client is still here!
		 * 2) confirmation for client: my message was delivered!
		 * The purpose of MSG_NOSIGNAL is to ignore the SIGPIPE signal that
		 * would be kill the process if there's a send() error (default
		 * behaviour, FSM knows why).
		 */
		int sent = send(clients[id]->getSocket(), &confirmation_byte, 1,
				MSG_NOSIGNAL);
		logf(LOG_DEBUG, "confirmation: sent %d bytes", sent);

		/* send() should return the number of bytes sent. If there's something
		 * wrong, we couldn't send the one byte (the value should be different
		 * from 1).
		 * We may assume that the client has disconnected.
		 */
		if(sent != 1) {
			logf(LOG_WARNING, "%s: connection lost", clients[id]->getIP());
			removeClient(id);
		}

		/* Otherwise, we can let the data guard take over:
		 */
		else {
			char debug_msg[BUFFER_SIZE];
			copyFirstLine(debug_msg, buffer_in);
			logf(LOG_DEBUG, "%s: received '%s'", clients[id]->getIP(),
					debug_msg);

			/* Here, the data guard takes over. The content of the input_buffer
			 * tells the connection handler what to do (that will take a lot of
			 * time). The response will be stored in the output_buffer.
			 */
			data_handler->setGameTask(buffer_in, received, clients[id]);
		}
	}
}

/**
 * TODO deprecated
 * This method handles the user input (server side command line interface).
 */
void
Network::handleStdInput(void)
{
	int received = read(STDIN_FILENO, buffer_in, BUFFER_SIZE);

	/* read() should return the number of bytes read. If something went wrong
	 * there, we don't want to handle the error, so let's crash:
	 */
	if(received < 0)
		throw new Exception("input failed");

	/* Copy the first line (it's all that's interesting):
	 */
	char command[BUFFER_SIZE];
	copyFirstLine(command, buffer_in);

	/* Check what command was entered:
	 */
	if(strstr(command,"shutdown")==command || strstr(command,"exit")==command
			|| strstr(command,"quit")==command || strstr(command,"sd")==command)
		data_handler->setTermSignal();

	if(strstr(command, "help") == command) {
		printf("\e[1mAvailable commands\e[0m\n");
		printf("  \e[32mquit|exit|shutdown|sd\e[0m   shut the server down\n");
	}
}

/**
 * This method copies the first line of a string. It checks the string for the
 * first appearance of a terminating zero character or a newline (\n).
 * @param dest The string where the first line shall be copied to.
 * @param src The string from where the first line is read.
 */
void
Network::copyFirstLine(char* dest, char const* src)
{
	int pos;
	strncpy(dest, src, pos = ((size_t)(strstr(src,"\n")-src) < strlen(src))
			? strstr(src,"\n")-src : strlen(src));
	dest[pos] = 0; // terminate
}

/**
 * This method correctly (logout, savegame) removes a client.
 * TODO deprecated, create and use session handler for this (via data handler)
 */
void
Network::removeClient(int id)
{
	send(clients[id]->getSocket(), &confirmation_byte, 0, MSG_NOSIGNAL);
	if(!data_handler->disconnect(id))
		logf(LOG_WARNING, "%s: disconnected client was not logged in",
				clients[id]->getIP());
	close(clients[id]->getSocket());
	clients.erase(clients.begin()+id);
}

