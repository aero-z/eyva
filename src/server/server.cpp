#include "server.h"

using namespace AyeLog;

Server::Server(int port) {
	data_guard = new DataGuard();
	confirmation_byte = 0;

	/* Create socket:
	 * AF_INET:     domain (ARPA, IPv4)
	 * SOCK_STREAM: type (stream socket: TCP)
	 * 0:           protocol (standard protocol)
	 */
	sockl = socket(AF_INET, SOCK_STREAM, 0);
	if(sockl < 0)
		throw new NetworkException("socket() failed");

	/* Clear the server_addr struct, then fill with appropriate data:
	 */
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;                  // use IPv4
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);   // allow all connections
	server_addr.sin_port = htons(port);                // port to listen to

	/* Bind socket to information contained by the struct that was just defined:
	 * sockfd:      socket that should bind to the address
	 * my_addr:     the address (IP and port, declared above) as type "sockaddr"
	 * addrlen:     size of the address struct
	 */
	if(bind(sockl, (sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		throw new NetworkException("bind() failed: %s", strerror(errno));
	}

	/* Start socket (we will use it to listen, since this is a server):
	 * sockl:         socket that should start listening
	 * CLIENTS_MAX:   #connections to keep in queue and to listen to
	 */
	if(listen(sockl, CLIENTS_MAX) == -1) {
		throw new NetworkException("listen() failed: %s", strerror(errno));
	}
	logf(LOG_NORMAL, "Listening on port %d ...", port);
}

/* PUBLIC METHODS */

void Server::run() {
	term_signal = false;
	while(!term_signal) {
		prepareFDSet();

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
		if(FD_ISSET(sockl, &socket_set))
			handleConnection();

		/* Cycle through all connections to check if there is data and react
		 * accordingly:
		 */
		for(unsigned int i = 0; i < clients.size(); i++) {
			if(FD_ISSET(clients[i]->getSocket(), &socket_set)) {
				handleData(i);
			}
		}

		/* Check if there is standard input:
		 */
		if(FD_ISSET(STDIN_FILENO, &socket_set))
			handleStdInput();
	}

	/* Close all sockets and quit:
	 */
	logf(LOG_NORMAL, "received shutdown signal, closing sockets ...");

	close(sockl);
	for(unsigned int i = 0; i < clients.size(); i++)
		close(clients[i]->getSocket());
	
	logf(LOG_NORMAL, "Bye!");
}

/* PRIVATE METHODS */

/* This methods updates the file descriptor set:
 */
void Server::prepareFDSet(void) {
	/* Before adding all used sockets to the fd_set, clear it:
	 */
	FD_ZERO(&socket_set);

	/* First, add the listening socket (for incoming connections), then cycle
	 * through the list of clients:
	 */
	FD_SET(sockl, &socket_set);
	for(unsigned int i = 0; i < clients.size(); i++)
		FD_SET(clients[i]->getSocket(), &socket_set);

	/* To control the server, we also listen to STDIN:
	 */
	FD_SET(STDIN_FILENO, &socket_set);
}

/* This method handles incoming connections:
 */
void Server::handleConnection(void) {
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
		throw new NetworkException("accept() failed");

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

/* This method handles incoming data from clients:
 */
void Server::handleData(int id) {
	/* Read data to buffer:
	 */
	int received = read(clients[id]->getSocket(), input_buffer, BUFFER_SIZE);
	logf(LOG_DEBUG, "received %d bytes", received);

	/* read() should return the number of bytes received. If the number is
	 * negative, there was an error, and we'll crash:
	 */
	if(received < 0)
		throw new NetworkException("read() failed");

	/* If the number of bytes received is equal to zero, the connection has been
	 * closed by the peer:
	 */
	if(received == 0) {
		logf(LOG_NORMAL, "> %s: connection closed by peer",
				clients[id]->getIP());
		/* TODO
		data_guard->disconnect(clients[id]->getSocket());
		*/
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
			/* TODO
			data_guard->disconnect(clients[id]->getSocket());
			*/
			clients.erase(clients.begin()+id);
		}

		/* Otherwise, we can let the data guard take over:
		 */
		else {
			char debug_msg[BUFFER_SIZE];
			copyFirstLine(debug_msg, input_buffer);
			logf(LOG_DEBUG, "%s: received '%s'", clients[id]->getIP(),
					debug_msg);

			/* Here, the data guard takes over. The content of the input_buffer
			 * tells the connection handler what to do (that will take a lot of
			 * time). The response will be stored in the output_buffer.
			 */
			data_guard->process(output_buffer, input_buffer);

			/* Handle the response generated by the connection handler:
			 */
			handleResponse();
		}
	}
}

/* This method handles the user input (server side command line interface):
 */
void Server::handleStdInput(void) {
	int received = read(STDIN_FILENO, input_buffer, BUFFER_SIZE);

	/* read() should return the number of bytes read. If something went wrong
	 * there, we don't want to handle the error, so let's crash:
	 */
	if(received < 0)
		throw new IOException("input failed");

	/* Copy the first line (it's all that's interesting):
	 */
	char command[BUFFER_SIZE];
	copyFirstLine(command, input_buffer);

	/* Check what command was entered:
	 */
	if(strstr(command,"shutdown")==command || strstr(command,"exit")==command
			|| strstr(command,"quit")==command || strstr(command,"sd")==command)
		term_signal = true;

	if(strstr(command, "help") == command) {
		printf("\e[1mAvailable commands\e[0m\n");
		printf("  \e[32mquit|exit|shutdown|sd\e[0m   shut the server down\n");
	}
}

/* This method copies everything from `src' to `dest' until a newline or the
 * terminating \0 (= strlen) appears:
 */
void Server::copyFirstLine(char* dest, char const* src) {
	int pos;
	strncpy(dest, src, pos = ((unsigned int)(strstr(src,"\n")-src)<strlen(src))
			? strstr(src,"\n")-src : strlen(src));
	dest[pos] = 0;                      // replace character after string by \0
}

/* This method handles the response generated by the connection handler:
 */
void Server::handleResponse(void) {
	int sent;

	/* In case that the first byte is set to zero, it's a broadcast message and
	 * shall be sent to all clients:
	 */
	if(output_buffer[0] == 0) {
		/* We set the first byte to a value other than 0, since strlen() would
		 * otherwise already stop at the first byte:
		 */
		output_buffer[0] = 32;
		logf(LOG_DEBUG, "broadcast message: '%s'", output_buffer);
		for(unsigned int i = 0; i < clients.size(); i++) {
			sent = send(clients[i]->getSocket(), output_buffer,
					strlen(output_buffer), MSG_NOSIGNAL);

			/* Check connection and disconnect in case of error:
			 */
			if(sent < 0) {
				logf(LOG_WARNING, "%s: connection lost", clients[i]->getIP());
				/* TODO
				data_guard->disconnect(clients[j]->getSocket());
				*/
				clients.erase(clients.begin()+i);
			}
		}
	}
	
	/* In case the first byte is NOT set to zero, it shall be interpreted as the
	 * client file descriptor:
	 */
	else {
		logf(LOG_DEBUG, "message to: %s on %s",
				clients[output_buffer[0]]->getIP(),
				clients[output_buffer[0]]->getSocket());
		sent = send(clients[output_buffer[0]]->getSocket(), output_buffer,
				strlen(output_buffer), MSG_NOSIGNAL);
		/* Check connection and disconnect in case of error:
		 */
		if(sent < 0) {
			logf(LOG_WARNING, "%s: connection lost",
					clients[output_buffer[0]]->getIP());
			/* TODO
			data_guard->disconnect(clients[output_buffer[0]]->getSocket());
			*/
			clients.erase(clients.begin()+output_buffer[0]);
		}
	}
}

