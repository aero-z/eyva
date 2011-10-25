#include "server.h"

using namespace AyeLog;

/* PUBLIC METHODS/CONSTRUCTOR ------------------------------------------------*/

Server::Server(int port) {
	this->port = port;
	connection_handler = new ConnectionHandler(this);

	/* clear the server_addr struct, then fill with appropriate data:
	 */
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;                  // use IPv4
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);   // allow all connections
	server_addr.sin_port = htons(port);                // port to listen to

	/* create listening socket:
	 * AF_INET:     domain (ARPA, IPv4)
	 * SOCK_STREAM: type (stream socket: TCP)
	 * 0:           protocol (standard protocol)
	 */
	sockl = socket(AF_INET, SOCK_STREAM, 0);
	if(sockl < 0)
		throw new NetworkException("socket() failed");

	/* bind socket:
	 * sockfd:      socket that should bind to the address
	 * my_addr:     the address (IP and port, declared above) as type "sockaddr"
	 * addrlen:     size of the address struct
	 */
	if(bind(sockl, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		throw new NetworkException("bind() failed: %s", strerror(errno));
	}

	/* start socket (listen):
	 * sockl:         socket that should start listening
	 * CLIENTS_MAX:   #connections to keep in queue and to listen to
	 */
	if(listen(sockl, CLIENTS_MAX) == -1) {
		throw new NetworkException("listen() failed");
	}
	logf(NORMAL_LOG, "Listening on port %d ...", port);
}

void Server::run() {
	/* We're going to check all the socket/file descriptors by using select()
	 * (connection, read, write, console input, etc).
	 * As select() needs an fd_set containing those socket descriptors, we're
	 * going to create a such:
	 */
	fd_set socket_set;

	bool term_signal;
	do {
		/* before adding all used sockets to the fd_set, clear it:
		 */
		FD_ZERO(&socket_set);

		/* first add the listening socket (for incoming connections), then
		 * cycle through the list of clients:
		 */
		FD_SET(sockl, &socket_set);
		for(int i = 0; i < connection_handler->countClients(); i++)
			FD_SET(connection_handler->getClient(i)->getSocket(), &socket_set);

		/* select() checks every socket in the socket_set, if there's something
		 * to do (e.g. data received, connection requested, ...)
		 * This method blocks until there's anything, so as soon as select()
		 * returns, we should have things to do:
		 */
		int selected = select(FD_SETSIZE, &socket_set, NULL, NULL, NULL);

		/* select() should return -1 if something went wrong. As we don't want
		 * to handle the error yet, just let's crash!
		 */
		if(selected < 0)
			throw new IOException("select() failed");

		/* otherwise, select() should have had success, and we can check what
		 * happened:
		 */
		else {
			/* Check if there is a connection request, and react accordingly:
			 */
			if(FD_ISSET(sockl, &socket_set)) {
				/* Accept the connection:
				 */
				int sock_new = accept(sockl, NULL, NULL);

				/* accept() should return -1 if something went wrong. Again,
				 * as we don't want to handle the error yet, crash!
				 */
				if(sock_new < 0)
					throw new NetworkException("accept() failed");

				/* Add the new client to the list of clients, if there's still
				 * space for. Otherwise reject the client (close the socket):
				 */
				if(clients.size() < CLIENTS_MAX) {
					connection_handler->addClient(new Client(sock_new));
				} else {
					close(sock_new);
				}
			}

			/* Cycle through all connections to check if there is data and react
			 * accordingly:
			 */
			for(int i = 0; i < connection_handler->countClients(); i++) {
				if(FD_ISSET(connection_handler->getClient(i)->getSocket(),
						&socket_set)) {
					/* Read data to buffer:
					 */
					int received = read(
							connection_handler->getClient(i)->socket, buffer,
							BUFFER_SIZE);

					/* read() should return the number of bytes received. If the
					 * number is negative, there was an error, and we'll crash:
					 */
					if(received < 0) {
						throw new NetworkException("read() failed");
					}

					/* If the number of bytes received is equal to zero, the
					 * the connection has been closed by peer:
					 */
					else if(received == 0) {
						connection_handler->removeClient(i);
					}

					/* If the number is positive, read to buffer and let the
					 * connection_handler take over:
					 */
					else {
						printf("interacting...\n");
						//connection_handler->interact(i, buffer);
					}
				}
			} // end "for"
		} // end "selected" handle
	} while(!term_signal);
	close(sockl);
}

/* PRIVATE METHODS/CONSTRUCTOR -----------------------------------------------*/

