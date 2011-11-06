#include "network.h"

using namespace AyeLog;

/**
 * Constructor
 * @param data_handler The data handler that is needed to communicate to the UI,
 *                     and that handles all data related stuff.
 * @param ip The server's IP address.
 * @param port The port on which the server is running on.
 */
Network::Network(DataHandler* data_handler, char const* ip, int port) {
	this->data_handler = data_handler;

	/* Create socket:
	 * AF_INET:     domain (ARPA, IPv4)
	 * SOCK_STREAM: type (stream socket)
	 * IPPROTO_TCP: protocol (TCP)
	 */
	sockc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sockc < 0)
		throw new Exception("socket() failed");
	
	/* Clear the server_addr struct, then fill with appropriate data:
	 */
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;            // use IPv4
	server_addr.sin_addr.s_addr = inet_addr(ip); // connect to given IP
	server_addr.sin_port = htons(port);          // ... and given port

	/* Connect to the server according to the information contained by the
	 * struct that was just defined:
	 */
	if(connect(sockc, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		throw new Exception("connect() failed: %s", strerror(errno));
	}

	logf(LOG_NORMAL, "Connection established to %s on port %d", ip, port);
}

/**
 * Destructor.
 */
Network::~Network(void) {
	// VOID
}


/* PUBLIC METHODS */

/**
 * This method checks the network socket if there is data on it, and it checks
 * the data handler if this object has been alerted by the UI, so there is data
 * to be sent to the server.
 */
void
Network::poll(void) {
	pollIn();
	pollOut();
}


/* PRIVATE METHODS */

/**
 * This method checks incoming network data and forwards them to the data
 * handler to alert the UI.
 */
void
Network::pollIn(void) {
	/* We'll add the connection socket to the fd_set that is checked by select()
	 * for available data on it (see below):
	 */
	FD_SET(sockc, &socket_set);

	/* select() checks every socket in the socket_set if there's some data on
	 * it.
	 * This method would block until there's anything, but since we just
	 * want to poll (in order for the data guard to go on), we don't block
	 * by setting the timeout to 0:
	 */
	select_timeout.tv_sec = 0;
	select_timeout.tv_usec = 0;
	int selected = select(FD_SETSIZE, &socket_set, NULL, NULL,
			&select_timeout);

	/* select() should return a -1 if something went wrong. As we have set a
	 * timeout, the error just indicates that there was no data after the
	 * timeout (usually we would crash here, but we'll just go on):
	 */
	if(selected >= 0) {
		if(FD_ISSET(sockc, &socket_set)) {
			/* Read data to buffer:
			 */
			int received = read(sockc, buffer_in, BUFFER_SIZE);

			/* read() should return the number of bytes received. If the number
			 * is negative, there was an error, and we'll crash:
			 */
			if(received < 0)
				throw new Exception("read() failed");
			
			/* If the number of bytes received is equal to zero, the connection
			 * has been closed by the server.
			 */
			if(received == 0)
				throw new Exception("client disconnect");
			
			/* OK, if we haven't crashed yet, the number of received bytes
			 * should be positive.
			 * The data handler processes the received bytes and alerts the UI:
			 */
			data_handler->setUITask(buffer_in, received);
		}
	}
}

/**
 * This method checks the data handler if there's data to be sent and reacts
 * accordingly.
 */
void
Network::pollOut(void) {
	/* Check if there's data to send. The packet will be stored to buffer_out,
	 * the length of the data will be returned:
	 */
	size_t command_len = data_handler->getNetworkTask(buffer_out);

	/* Command [00 NULL] means: data should not be sent:
	 */
	if(buffer_out[0] == 0)
		return;

	/* MSG_NOSIGNAL avoids a program crash by a SIGPIPE that would normally be
	 * raised if there's a sending error. That's the default behaviour, FSM
	 * knows why:
	 */
	int sent = send(sockc, buffer_out, command_len, MSG_NOSIGNAL);

	/* send() should return the number of bytes sent. If the number is
	 * negative, there was an error, so we'll crash:
	 */
	if(sent < 0)
		throw new Exception("send() failed");

	/* If the number of bytes sent is equal to zero, there was an error,
	 * too, so we crash:
	 */
	if(sent == 0)
		throw new Exception("no bytes sent");
}
