#include "session.h"

using namespace AyeLog;

Session::Session(char const* ip, int port) {
	/* Create socket:
	 * AF_INET:     domain (ARPA, IPv4)
	 * SOCK_STREAM: type (stream socket: TCP)
	 * 0:           protocol (standard protocol)
	 */
	sockc = socket(AF_INET, SOCK_STREAM, 0);
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
	logf(LOG_NORMAL, "Connected to %s on port %d ...", ip, port);
}

/* PUBLIC METHODS */

void Session::run(void) {
	bool term_signal = false;
	while(!term_signal) {
		prepareFDSet();

		/* select() checks every socket in the socket_set if there's some data
		 * on it.
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
				logf(LOG_DEBUG, "input from server");
			}
		}

		// send TODO
		buffer_out[0] = 'h';
		buffer_out[1] = 'e';
		buffer_out[2] = 'l';
		buffer_out[3] = 'l';
		buffer_out[4] = 'o';
		send(sockc, buffer_out, strlen(buffer_out), MSG_NOSIGNAL);
	
		// receive
		read(sockc, buffer_in, BUFFER_SIZE);
	
		// quit
		term_signal = true;
	}

	send(sockc, buffer_out, 0, MSG_NOSIGNAL);
	close(sockc);
}

/* The select() command checks the availability of data on sockets. select()
 * requires the sockets to be in a fd_set, so we'll prepare the fd_set
 * appropriately:
 */
void Session::prepareFDSet(void) {
	/* Add the connection socket to the fd_set that is checked by select() for
	 * available data on it:
	 */
	FD_SET(sockc, &socket_set);
}

/* This method handles incoming data from the server:
 */
void Session::handleData() {
	/* Read data to buffer:
	 */
	int received = read(sockc, buffer_in, BUFFER_SIZE);

	/* read() should return the number of bytes received. If the number is
	 * negative, there was an error, and we'll crash:
	 */
	if(received < 0)
		throw new Exception("read() failed");
	
	/* If the number of bytes received is equal to zero, the connection has been
	 * closed by the server.
	 */
	if(received == 0)
		throw new Exception("client disconnect");
	
	/* OK, if we haven't crashed yet, the number of received bytes should be
	 * positive.
	 * The data guard may take over at this point:
	 */
	/* TODO
	data_guard->process(buffer_out, buffer_in);
	*/
}
