#include "network.h"

using namespace AyeLog;

/**
 * Constructor.
 * The network handler starts listening to a network socket for incoming
 * connections.
 * @param port The TCP port to listen to.
 */
Network::Network(int port)
{
	pipe = new Pipe();
	game = new Game(pipe);

	/* Create socket:
	 * AF_INET:     domain (ARPA, IPv4)
	 * SOCK_STREAM: type (stream socket)
	 * IPPROTO_TCP: protocol (TCP)
	 */
	sockc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sockc < 0)
		throw new Exception("socket() failed");
	
	/* Make the socket nonblocking (so if the program crashes the socket will be
	 * released immediately):
	 */
	int option = 1; // TODO find out what this does
	setsockopt(sockc, SOL_SOCKET, SO_REUSEADDR, (char*)&option, sizeof(option));

	/* Prepare information for binding socket to:
	 */
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));    // fill with zero, then:
	server_addr.sin_family = AF_INET;                // - use IPv4
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // - allow all connections
	server_addr.sin_port = htons(port);              // - port to listen to

	/* Bind socket to information contained by the struct that was just defined:
	 */
	if(bind(sockc, (sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		throw new Exception("bind() failed: %s", strerror(errno));
	}

	/* Start socket as listener:
	 * sockc:         socket that should start listening
	 * SESSIONS_MAX:  number of connections to keep in queue and to listen to
	 */
	if(listen(sockc, QUEUE_SIZE) < 0) {
		throw new Exception("listen() failed: %s", strerror(errno));
	}

	logf(LOG_NORMAL, "Listening on port %d ...", port);
}

/**
 * Destructor.
 * All session are correctly closed (savegame, logout) and the server side
 * network is shut down.
 */
Network::~Network(void)
{
	logf(LOG_NORMAL, "received shutdown signal, closing sockets ...");

	/* Close the connection socket:
	 */
	close(sockc);

	/* Close all session sockets:
	 */
	for(it = sessions.begin(); it != sessions.end(); it++) {
		close(it->first);
	}

	/* This will remove all elements from the map and call their destructors:
	 */
	sessions.clear();

	delete game;
	delete pipe;
}


/* PUBLIC METHODS */


/**
 * This method checks the open sockets for data and sends back data.
 */
void
Network::poll(void)
{
	logf(LOG_DEBUG, "handling %d sessions ...", sessions.size());
	pollIn();
	pollOut();
}


/* PRIVATE METHODS */


/**
 * This method checks the sockets for data. select() is used, that will block
 * until there is data, so as long as there's no data, the program will sleep
 * here.
 */
void
Network::pollIn(void)
{
	fd_set socket_set;

	/* Before adding all used sockets to the fd_set, clear it:
	 */
	FD_ZERO(&socket_set);

	/* First, add the listening socket (for incoming connections), then cycle
	 * through the sessions:
	 */
	FD_SET(sockc, &socket_set);
	for(it = sessions.begin(); it != sessions.end(); it++)
		FD_SET(it->first, &socket_set);

	/* select() checks every socket in the socket_set, if there's some data on
	 * it (e.g. data received, connection requested, ...)
	 * This method blocks until there's anything, so as soon as select()
	 * returns, we should have things to do:
	 */
	int selected = select(FD_SETSIZE, &socket_set, NULL, NULL, NULL);

	/* select() should return -1 if something went wrong. As we don't want to
	 * handle the error yet, just let's crash!
	 */
	if(selected < 0)
		throw new Exception("select() failed");

	/* Check for connection request:
	 */
	if(FD_ISSET(sockc, &socket_set)) {
		logf(LOG_DEBUG, "incoming connection ...");
		handleConnection();
	}

	/* Check for data on a session's socket:
	 */
	for(it = sessions.begin(); it != sessions.end(); it++)
		if(FD_ISSET(it->first, &socket_set)) {
			logf(LOG_DEBUG, "data on socket %d ...", it->first);
			handleData(it->first);
		}
}

/**
 * This method handles incoming connections. For each connection accepted, it
 * creates a Client object and stores it to the std::vector.
 */
void
Network::handleConnection(void)
{
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);

	/* Accept the connection, storing client information to the struct that was
	 * just defined:
	 */
	int sock_new = accept(sockc, (sockaddr*)&client_addr, &client_addr_len);

	/* accept() should return -1 if something went wrong. As we don't want to
	 * handle the error yet, crash:
	 */
	if(sock_new < 0)
		throw new Exception("accept() failed");

	/* Create a new session, if there's still space for it; otherwise reject the
	 * client (close the socket):
	 */
	if(sessions.size() < QUEUE_SIZE) {
		sessions.insert(std::pair<int, Session*>(sock_new,
				new Session(sock_new, inet_ntoa(client_addr.sin_addr), pipe)));
		logf(LOG_NORMAL, "> \e[32m%s\e[0m: new connection on socket %d",
				sessions[sock_new]->getIP(), sock_new);
	} else {
		close(sock_new);
	}
}

/**
 * This method handles incoming data on a socket.
 * @param socket The socket which holds the data.
 */
void
Network::handleData(int socket)
{
	/* Read data to buffer:
	 */
	int received = read(socket, buffer_in, BUFFER_SIZE);

	/* read() should return the number of bytes received. If the number is
	 * negative, there was an error, thus crash:
	 */
	logf(LOG_DEBUG, "received %d bytes", received);
	if(received < 0)
		throw new Exception("read() failed");

	/* If the number of bytes received is equal to zero, the connection has been
	 * closed by the peer:
	 */
	if(received == 0) {
		logf(LOG_NORMAL, "\e[33m%s\e[0m: connection closed by peer",
				sessions[socket]->getIP());
		close(socket);
		sessions.erase(socket);
	}

	/* If the number is positive, there is data to handle:
	 */
	else {
		/* Send confirmation byte, to make sure the client is still there:
		 */
		char confirmation_byte = 10;
		int sent = send(socket, &confirmation_byte, 1, MSG_NOSIGNAL);

		/* Check if successfully confirmation byte was successfully sent;
		 * otherwise close session:
		 */
		logf(LOG_DEBUG, "confirmation: sent %d bytes", sent);
		if(sent != 1) {
			logf(LOG_WARNING, "%s: connection lost", sessions[socket]->getIP());
			close(socket);
			sessions.erase(socket);
		}

		/* Otherwise, the session may handle the data:
		 */
		else {
			sessions[socket]->handle(buffer_in, received);
		}
	}
}

/**
 * After having handled all the incoming data, the internal server system has
 * filled the network handler's pipe with data to be sent to the clients.
 * Thus, this method will check all the messages in the pipe.
 */
void
Network::pollOut(void)
{
	while(pipe->check()) {
		size_t message_len = pipe->fetch(buffer_out);

		/* The byte zero holds the session's socket file descriptor:
		 */
		int socks = buffer_out[0];

		logf(LOG_DEBUG, "sending data to %s on socket %d",
				sessions[socks]->getIP(), socks);
		 
		/* Default behaviour of send() is to raise a SIGPIPE (and thus to cause
		 * a program crash) whenever it fails (FSM knows why). To avoid that, we
		 * set MSG_NOSIGNAL.
		 * TODO make Mac OS X compatible (MSG_NOSIGNAL is SO_NOSIGPIPE)
		 */
		int sent = send(socks, buffer_out, message_len, MSG_NOSIGNAL);

		/* If there was an error sending, the client may be assumed as
		 * disconnected, and thus the session may be closed:
		 */
		if(sent <= 0) {
			logf(LOG_WARNING, "%s: connection lost", sessions[socks]->getIP());
			close(socks);
			sessions.erase(socks);
		}
	}
}

