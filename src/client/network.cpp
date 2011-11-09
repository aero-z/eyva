#include "network.h"

using namespace AyeLog;

/**
 * Constructor
 * @param pm The postmaster that is needed to communicate to the UI.
 */
Network::Network(Postmaster* pm)
{
	this->pm = pm;
	connected = false;
	buffer_out = new char[BUFFER_SIZE];
	buffer_in = new char[BUFFER_SIZE];
}

/**
 * Destructor.
 */
Network::~Network(void)
{
	// TODO
}


/* PUBLIC METHODS */


/**
 * This method checks the network socket if there is data on it, and it checks
 * the data handler if this object has been alerted by the UI, so there is data
 * to be sent to the server.
 */
void
Network::poll(void)
{
	if(connected)
		pollIn();
	pollOut();
}


/* PRIVATE METHODS */


/**
 * This method connects the client to a server.
 * @param ip The server's IP address.
 * @param port The port on which the server is running on.
 */
bool
Network::connect(char const* ip, int port)
{
	/* Create socket:
	 * AF_INET:     domain (ARPA, IPv4)
	 * SOCK_STREAM: type (stream socket)
	 * IPPROTO_TCP: protocol (TCP)
	 */
	logf(LOG_DEBUG, "creating socket ...");
	sockc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sockc < 0) {
		logf(LOG_ERROR, "creating socket failed");
		return false;
	}
	
	/* The socket shall just be polled, so set it to non-blocking mode, which
	 * allows to go on if there's no data on the socket (remember, there's also
	 * a UI I/O going on):
	 */
	fcntl(sockc, F_SETFL, O_NONBLOCK);

	/* Prepare the server information for use with connect().
	 */
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;            // use IPv4
	server_addr.sin_addr.s_addr = inet_addr(ip); // connect to given IP
	server_addr.sin_port = htons(port);          // ... and given port

	/* Connect to the server according to the information contained by the
	 * struct that was just defined:
	 */
	logf(LOG_DEBUG, "connecting to %s:%d ...", ip, port);
	if(::connect(sockc, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		logf(LOG_ERROR, "connect() failed: %s", strerror(errno));
		return false;
	}

	logf(LOG_NORMAL, "connection established to %s:%d", ip, port);
	return true;
}

/**
 * This method closes the connection to the server.
 */
void
Network::disconnect(void)
{
	/* Send a zero-byte message, which will close the connection.
	 * The default behaviour of send() is to invoke a sigpipe by the system that
	 * will immediately kill the program (FSM knows why). To avoid that, send()
	 * is called with the MSG_NOSIGNAL flag.
	 * TODO make Mac OS X compatible (MSG_NOSIGNAL is SO_NOSIGPIPE).
	 */
	send(sockc, NULL, 0, MSG_NOSIGNAL);

	/* Close the socket:
	 */
	close(sockc);
	connected = false;
}

/**
 * This method checks incoming network data and forwards them to the UI.
 */
void
Network::pollIn(void)
{
	/* Read data to buffer:
	 */
	int received = read(sockc, buffer_in, BUFFER_SIZE);

	/* If the number of bytes received is equal to zero, the connection has been
	 * closed by the server:
	 */
	if(received == 0)
		disconnect();
	
	/* read() should return the number of bytes received. If there was an error,
	 * -1 is returned.
	 * Since the socket is in non-blocking mode, this is likely to happen, so
	 * just ignore it.
	 * Process the received bytes if the number is positive:
	 */
	if(received > 0)
		pm->send(BOX_UI, buffer_in);
}

/**
 * This method checks the postmaster for new messages and processes them.
 */
void
Network::pollOut(void)
{
	/* Check for new messages in the postbox. The message will be stored to
	 * buffer_out, the length of the data will be returned:
	 */
	for(size_t msg_len = pm->fetch(buffer_out, BOX_NETWORK);
			msg_len > 0; ) {

		/* Command [01 CONNECT] requires additional action:
		 */
		if(buffer_out[1] == 1) {
			/* Make sure that there is no connection:
			 */
			disconnect();

			/* Prepare required data and connect:
			 */
			// TODO connect according to the message
		}
	
		/* MSG_NOSIGNAL avoids a program crash by a SIGPIPE that would normally
		 * be invoked if there's a sending error. That's the default behaviour,
		 * FSM knows why.
		 * TODO make Mac OS X compatible (MSG_NOSIGNAL is SO_NOSIGPIPE)
		 */
		int sent = send(sockc, buffer_out, msg_len, MSG_NOSIGNAL);

		/* send() should return the number of bytes sent. If the number is
		 * negative or equal to zero, there must have been an error, so close
		 * the connection:
		 */
		if(sent <= 0)
			disconnect();
	}
}

