#include "network.h"

using namespace AyeLog;

/**
 * Constructor.
 * @param data_handler The data handler that is needed to communicate to the
 *                     game object.
 * @param port The TCP port to listen to.
 * @throws Exception If there was an error while setting up the network
 *                   connection.
 */
Network::Network(DataHandler* data_handler, int port) {
	this->data_handler = data_handler;
	confirmation_byte = 0;

	/* Create socket:
	 * AF_INET:     domain (ARPA, IPv4)
	 * SOCK_STREAM: type (stream socket)
	 * IPPROTO_TCP: protocol (TCP)
	 */
	sockl = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sockl < 0)
		throw new Exception("socket() failed");

	/* Clear the server_addr struct, then fill with appropriate data:
	 */
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;                  // use IPv4
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);   // allow all connections
	server_addr.sin_port = htons(port);                // port to listen to

	/* Bind socket to information contained by the struct that was just defined:
	 * sockl:       socket that should bind to the address
	 * server_addr: the address (IP and port, declared above) as type "sockaddr"
	 * addrlen:     size of the address struct
	 */
	if(bind(sockl, (sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		throw new Exception("bind() failed: %s", strerror(errno));
	}

	/* Start socket (we will use it to listen, since this is a server):
	 * sockl:         socket that should start listening
	 * CLIENTS_MAX:   #connections to keep in queue and to listen to
	 */
	if(listen(sockl, CLIENTS_MAX) < 0) {
		throw new Exception("listen() failed: %s", strerror(errno));
	}

	logf(LOG_NORMAL, "Listening on port %d ...", port);
}

/**
 * Destructor.
 * All clients are correctly (savegame, logout) disconected and the network
 * connection is shut down.
 */
Network::~Network(void) {
	/* Close all sockets and quit:
	 */
	logf(LOG_NORMAL, "received shutdown signal, closing sockets ...");

	close(sockl);
	for(size_t i = 0; i < clients.size(); i++) {
		removeClient(i);
	}
}


/* PUBLIC METHODS */

/**
 * This method polls incoming data (new connections, data, user input
 * (deprecated)) and sends data to clients if required by the data handler.
 */
void
Network::poll(void) {
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
Network::pollIn(void) {
	/* Before adding all used sockets to the fd_set, clear it:
	 */
	FD_ZERO(&socket_set);

	/* First, add the listening socket (for incoming connections), then cycle
	 * through the list of clients:
	 */
	FD_SET(sockl, &socket_set);
	for(size_t i = 0; i < clients.size(); i++)
		FD_SET(clients[i]->getSocket(), &socket_set);

	/* To control the server, we also listen to STDIN:
	 */
	FD_SET(STDIN_FILENO, &socket_set);

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

	/* If we haven't crashed yet, check if there is a connection request, and
	 * react accordingly:
	 */
	if(FD_ISSET(sockl, &socket_set))
		handleConnection();

	/* Cycle through all connections to check if there is data and react
	 * accordingly:
	 */
	for(size_t i = 0; i < clients.size(); i++) {
		if(FD_ISSET(clients[i]->getSocket(), &socket_set)) {
			handleData(i);
		}
	}

	/* TODO deprecated
	 * Check if there is standard input:
	 */
	if(FD_ISSET(STDIN_FILENO, &socket_set))
		handleStdInput();
}

/**
 * This method checks the data handler for a command to be sent to the client
 * and sends it if required.
 */
void
Network::pollOut(void) {
	int command_len = data_handler->getNetworkTask(buffer_out, &targets);

	/* Command [00 NULL] means: no data should be sent over the network:
	 */
	if(buffer_out[0] == 0)
		return;

	/* Otherwise, we're going to cycle through all the clients that have been
	 * put into the `targets' vector:
	 */
	int sent;
	for(size_t i = 0; i < targets.size(); i++) {
		logf(LOG_DEBUG, "message to: %s on %s",
				targets[i]->getIP(),
				targets[i]->getSocket());

		sent = send(targets[i]->getSocket(), buffer_out, command_len,
				MSG_NOSIGNAL);

		/* Check connection and disconnect in case of error:
		 */
		if(sent < 0) {
			logf(LOG_WARNING, "%s: connection lost",
					targets[i]->getIP());
			removeClient(i);
		}
	}
}

/**
 * This method handles incoming connections. For each connection accepted, it
 * creates a Client object and stores it to the std::vector.
 */
void
Network::handleConnection(void) {
	/* Accept the connection:
	 * sockl:       listening socket for establishing a connection
	 * client_addr: struct to store client information
	 * client_addr: (size) of struct
	 */
	int sock_new = accept(sockl, (sockaddr *)&client_addr,
			&client_addr_len);

	/* accept() should return -1 if something went wrong. Again, as we don't
	 * want to handle the error yet, crash!
	 */
	if(sock_new < 0)
		throw new Exception("accept() failed");

	/* Add the new client to the list of clients, if there's still space for.
	 * Otherwise reject the client (close the socket):
	 */
	if(clients.size() < CLIENTS_MAX) {
		clients.push_back(new Client(sock_new,inet_ntoa(client_addr.sin_addr)));
		logf(LOG_NORMAL, "\e[32m%s\e[0m: new connection",
				clients[clients.size()-1]->getIP());
		logf(LOG_DEBUG, "new connection established on socket %d",
				clients[clients.size()-1]->getSocket());
	} else {
		close(sock_new);
	}
}

/**
 * This method handles incoming data from a client.
 * @param id The client's ID (which is also the position in the std::vector the
 *           client is stored in).
 */
void
Network::handleData(int id) {
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
		/* TODO
		data_guard->disconnect(clients[id]->getSocket());
		*/
		close(clients[id]->getSocket());
		clients.erase(clients.begin()+id);
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
			data_handler->setGameTask(buffer_in, received);
		}
	}
}

/**
 * TODO deprecated
 * This method handles the user input (server side command line interface).
 */
void
Network::handleStdInput(void) {
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
Network::copyFirstLine(char* dest, char const* src) {
	int pos;
	strncpy(dest, src, pos = ((size_t)(strstr(src,"\n")-src) < strlen(src))
			? strstr(src,"\n")-src : strlen(src));
	dest[pos] = 0; // terminate
}

/**
 * This method correctly (logout, savegame) removes a client.
 */
void
Network::removeClient(int id) {
	send(clients[id]->getSocket(), &confirmation_byte, 0, MSG_NOSIGNAL);
	/* TODO
	data_handler->disconnect(client[id]->getSocket());
	*/
	close(clients[id]->getSocket());
	clients.erase(clients.begin()+id);
}

