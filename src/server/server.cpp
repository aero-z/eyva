#include "server.h"

using namespace AyeLog;

Server::Server(int port) {
	client_addr_len = sizeof(client_addr);

	/* AF_INET:     domain (ARPA, IPv4)
	 * SOCK_STREAM: type (stream socket: TCP)
	 * 0:           protocol (standard protocol)
	 */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		throw new NetworkException("socket() failed");

	setNonBlocking(sockfd);     // so we can also go on if there's no content

	struct sockaddr_in my_addr;
	my_addr.sin_addr.s_addr = INADDR_ANY;   // allow connections from everywhere
	my_addr.sin_port = htons(port);         // port to listen to
	my_addr.sin_family = AF_INET;           // use IPv4

	/* sockfd:      socket that should bind to the address
	 * my_addr:     the address (IP and port, as declared above)
	 * addrlen:     size of the address struct
	 */
	if(bind(sockfd, (sockaddr*)&my_addr, sizeof(my_addr)) < 0) {
		throw new NetworkException("bind() failed: %s", strerror(errno));
	}

	/* sockfd:      socket that should start listening
	 * 3:           number of connections to keep in queue
	 */
	if(listen(sockfd, 3) == -1) {
		throw new NetworkException("listen() failed");
	}

	logf(NORMAL_LOG, "Listening on port %d ...", port);
}

bool Server::run() {
	/* Accept incoming connections:
	 * sockfd:      socket that should accept connections
	 * client_addr: the address (IP and port) of the client
	 * address_len: size of the address struct, as socklen_t*
	 */
	csockfd = accept(sockfd, (sockaddr*)&client_addr, &client_addr_len);
	if(csockfd > 0) {
		/* accept */
		logf(NORMAL_LOG, "\e[32m%s:\e[0m connection established",
				inet_ntoa(client_addr.sin_addr));
		setNonBlocking(csockfd);
		clients.push_back(new Client(csockfd, inet_ntoa(client_addr.sin_addr)));
	}

	/* receive */
	int read_len, write_res;
	for(unsigned int i = 0; i < clients.size(); i++) {
		read_len = read(clients[i]->getSocket(), buf, BUFFER_SIZE);
		if(read_len <= 0) {
			if(read_len < 0) {
				logf(WARNING_LOG, "%s: connection crash: %s",
						clients[i]->getIPName(), strerror(errno));
			} else if(read_len == 0) {
				logf(NORMAL_LOG, "%s: connection closed",
						clients[i]->getIPName());
			}
			clients.erase(clients.begin()+i);
		} else {
			printf("socket %d: received bytes = %d (%d)\n",
					clients[i]->getSocket(), read_len, BUFFER_SIZE);
			char message[2048];
			sprintf(message, "[%d]", buf[0]);
			for(int j = 1; j < BUFFER_SIZE; j++)
				snprintf(message, 2048, "%s [%d]", message, buf[j]);
			logf(NORMAL_LOG, "received: %s (%s)", message, buf);
			write_res = write(clients[i]->getSocket(), "Thanks!\n", 9);
			if(write_res >= 0) {
				logf(NORMAL_LOG, "sent: \"Thanks!\"");
			} else {
				logf(WARNING_LOG, "could not send \"Thanks!\": %s",
						strerror(errno));
			}
		}
	}

	sleep(1);
	return true; // TODO let's run forever, for the moment
}

void Server::setNonBlocking(int sockfd) {
	int old_modes;
	if((old_modes = fcntl(sockfd, F_GETFL, 0)) < 0)
		throw new NetworkException("setNonBlocking() failed");
	fcntl(sockfd, F_SETFL, old_modes | O_NONBLOCK | SO_REUSEADDR);
}
