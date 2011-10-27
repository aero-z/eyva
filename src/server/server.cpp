#include "server.h"

using namespace AyeLog;

Server::Server(int port) {
	this->port = port;
	connection_handler = new ConnectionHandler();
	confirmation_byte = 0;

	/* Clear the server_addr struct, then fill with appropriate data:
	 */
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;                  // use IPv4
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);   // allow all connections
	server_addr.sin_port = htons(port);                // port to listen to

	/* Create listening socket:
	 * AF_INET:     domain (ARPA, IPv4)
	 * SOCK_STREAM: type (stream socket: TCP)
	 * 0:           protocol (standard protocol)
	 */
	sockl = socket(AF_INET, SOCK_STREAM, 0);
	if(sockl < 0)
		throw new NetworkException("socket() failed");

	/* Bind socket:
	 * sockfd:      socket that should bind to the address
	 * my_addr:     the address (IP and port, declared above) as type "sockaddr"
	 * addrlen:     size of the address struct
	 */
	if(bind(sockl, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		throw new NetworkException("bind() failed: %s", strerror(errno));
	}

	/* Start socket (listen):
	 * sockl:         socket that should start listening
	 * CLIENTS_MAX:   #connections to keep in queue and to listen to
	 */
	if(listen(sockl, CLIENTS_MAX) == -1) {
		throw new NetworkException("listen() failed: %s", strerror(errno));
	}
	logf(NORMAL_LOG, "Listening on port %d ...", port);
}

/* PUBLIC METHODS */

void Server::run() {
	/* We're going to check all the socket/file descriptors by using select()
	 * (connection, read, write, console input, etc).
	 * As select() needs an fd_set containing those socket descriptors, we're
	 * going to create a such:
	 */
	fd_set socket_set;

	bool term_signal = false;
	while(!term_signal) {
		/* Before adding all used sockets to the fd_set, clear it:
		 */
		FD_ZERO(&socket_set);

		/* First, add the listening socket (for incoming connections), then
		 * cycle through the list of clients:
		 */
		FD_SET(sockl, &socket_set);
		for(unsigned int i = 0; i < clients.size(); i++)
			FD_SET(clients[i]->getSocket(), &socket_set);

		/* To control the server, we also listen to STDIN:
		 */
		FD_SET(STDIN_FILENO, &socket_set);

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

		/* If we haven't crashed yet, check if there is a connection request,
		 * and react accordingly:
		 */
		if(FD_ISSET(sockl, &socket_set)) {
			/* Accept the connection:
			 * sockl:       listening socket for establishing a connection
			 * client_addr: struct to store client information
			 * client_addr: (size) of struct
			 */
			int sock_new = accept(sockl, (sockaddr*)&client_addr,
					&client_addr_len);

			/* accept() should return -1 if something went wrong. Again,
			 * as we don't want to handle the error yet, crash!
			 */
			if(sock_new < 0)
				throw new NetworkException("accept() failed");

			/* Add the new client to the list of clients, if there's still
			 * space for. Otherwise reject the client (close the socket):
			 */
			if(clients.size() < CLIENTS_MAX) {
				clients.push_back(new Client(sock_new,
						inet_ntoa(client_addr.sin_addr)));
				logf(NORMAL_LOG, "\e[32m%s\e[0m: new connection",
						clients[clients.size()-1]->getIP());
			} else {
				close(sock_new);
			}
		}

		/* Cycle through all connections to check if there is data and react
		 * accordingly:
		 */
		for(unsigned int i = 0; i < clients.size(); i++) {
			if(FD_ISSET(clients[i]->getSocket(), &socket_set)) {
				/* Read data to buffer:
				 */
				int received = read(clients[i]->getSocket(), input_buffer,
						BUFFER_SIZE);

				/* read() should return the number of bytes received. If the
				 * number is negative, there was an error, and we'll crash:
				 */
				if(received < 0)
					throw new NetworkException("read() failed");

				/* If the number of bytes received is equal to zero, the
				 * the connection has been closed by peer:
				 */
				if(received == 0) {
					logf(NORMAL_LOG, "> %s: connection closed by peer",
							clients[i]->getIP());
					/* TODO
					connection_handler->disconnect(
							clients[i]->getSocket());
					*/
					clients.erase(clients.begin()+i);
				}

				/* If the number is positive, we have successfully received
				 * data:
				 */
				else {
					/* First, we send a confirmation message, the purpose
					 * of which being:
					 * 1) confirmation for server: client is still here!
					 * 2) confirmation for client: my message was delivered!
					 * The purpose of MSG_NOSIGNAL is to ignore the SIGPIPE
					 * signal that would be kill the process if there's a
					 * send() error (default behaviour, FSM knows why).
					 */
					int sent = send(clients[i]->getSocket(),
							&confirmation_byte, 1, MSG_NOSIGNAL);

					/* send() should return the number of bytes sent. If
					 * there's something wrong, we couldn't send the one
					 * byte (the value should be different from 1).
					 * We may assume that the client has disconnected.
					 */
					if(sent != 1) {
						logf(WARNING_LOG, "%s: connection lost",
								clients[i]->getIP());
						/* TODO
						connection_handler->disconnect(
								clients[i]->getSocket());
						*/
						clients.erase(clients.begin()+i);
					}

					/* Otherwise, we can let the connection handler take
					 * over:
					 */
					else {
						char debug_msg[BUFFER_SIZE];
						copyFirstLine(debug_msg, input_buffer);
						logf(DEBUG_LOG, "%s: received '%s'",
								clients[i]->getIP(), debug_msg);
					}
				}
			}
		}

		/* Check if there was standard input:
		 */
		if(FD_ISSET(STDIN_FILENO, &socket_set)) {
			int received = read(STDIN_FILENO, input_buffer, BUFFER_SIZE);

			/* read() should return the number of bytes read. If something went
			 * wrong there, we don't want to handle the error, so let's crash:
			 */
			if(received < 0)
				throw new IOException("input failed");

			/* Copy the first line (it's all that's interesting):
			 */
			char command[BUFFER_SIZE];
			copyFirstLine(command, input_buffer);

			/* Check what command was entered:
			 */
			if(strstr(command, "shutdown") == command)
				term_signal = true;
			if(strstr(command, "help") == command) {
				printf("\e[1mAvailable commands\e[0m\n");
				printf("  \e[32mshutdown\e[0m   shut the server down\n");
			}
		}
	} // end endless loop (if term_signal == true)

	/* Close all sockets and quit:
	 */
	logf(NORMAL_LOG, "received shutdown signal, closing sockets ...");

	close(sockl);
	for(unsigned int i = 0; i < clients.size(); i++)
		close(clients[i]->getSocket());
	
	logf(NORMAL_LOG, "Bye!");
}

/* PRIVATE METHODS */

void Server::copyFirstLine(char* dest, char const* src) {
	int pos;
	strncpy(dest, src, (pos = strstr(src,"\n")-src)); // copy to the newline
	dest[pos] = 0;                                    // replace newline by \0
}

