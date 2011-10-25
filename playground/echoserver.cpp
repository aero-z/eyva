#include <cstdio>
#include <cstdlib>       // misc functions (strtol and else)
#include <vector>        // for vectors
#include <sys/socket.h>  // sockets definitions
#include <sys/types.h>   // socket types
#include <arpa/inet.h>   // inet (3) functions
#include <cstring>       // memset()
#include <unistd.h>      // read()
#include <fcntl.h>       // for O_NONBLOCK
#include <ctime>         // for sleep (clock_t type)

#define BUFFER_SIZE 1024

class Client {
	public:
		int sockc;
		Client(int sockc) {
			this->sockc = sockc;
		}
};

std::vector<Client*> clients;

void sleep(double seconds) {
	clock_t end;
	end = clock() + seconds*CLOCKS_PER_SEC;
	while(clock() < end);
}

void setNonBlocking(int fd) {
	int flags;
#if defined(O_NONBLOCK)
	/* This part is executed if the operating system does it the POSIX way. */
	if((flags = fcntl(fd, F_GETFL, 0)) == -1)
		flags = 0;
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
	/* This part is for all the others ("the old way") */
	flags = 1;
	ioctl(fd, FIOBIO, &flags);
#endif
}

int main(int argc, char** argv) {
	int sockl;                     // connection socket
	struct sockaddr_in servaddr;   // socket address structure
	char buffer[BUFFER_SIZE];      // character buffer
	
	/* get port number from command line input */

	short int port = 1251;
	char* endptr;
	if(argc >= 2) {
		port = strtol(argv[1], &endptr, 10);
	}

	/* set all bytes of serveraddr (of type sockaddr_in) to zero, then fill */

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;                // use IPv4
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // allow all connections
	servaddr.sin_port = htons(port);              // listening to this port

	/* create listening socket
	 * AF_INET = IPv4
	 * SOCK_STREAM = TCP
	 * 0 = protocol (?)
	 */

	if((sockl = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("error creating socket()\n");
		exit(EXIT_FAILURE);
	}

	/* if the socket already exists from before (maybe the server crashed?),
	 * reuse the old socket (otherwise bind() (see below) will fail)
	 */
	
	if(setsockopt(sockl, SOL_SOCKET, SO_REUSEADDR, NULL, sizeof(int)) == -1) {
		perror("error calling setsockopt()");
		//exit(EXIT_FAILURE);
	}

	/* bind() socket address to the listening socket */

	if(bind(sockl, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		perror("error calling bind()");
		exit(EXIT_FAILURE);
	}

	/* listen() and keep at most 3 connections in queue */

	if(listen(sockl, 3) < 0) {
		printf("error calling listen()\n");
		exit(EXIT_FAILURE);
	}

	printf("listening on port %d\n", port);
	
	/* prepare for infinite loop */

	fd_set socks;         // create an fd_set (required for select())

	//setNonBlocking(sockl);
	bool shut_down = false;
	while(!shut_down) {
		FD_ZERO(&socks);        // clear the fd_set
		FD_SET(sockl, &socks);  // add the connection socket to the fd_set
		for(int i = 0; i < clients.size(); i++) {
			FD_SET(clients[i]->sockc, &socks);
		}

		printf("%d clients ; waiting for select()...\n", clients.size());
		int selected = select(FD_SETSIZE, &socks, NULL, NULL, NULL);
		printf("input received\n");
		if(selected < 0) { // there was an error
			printf("error with select()\n");
			exit(EXIT_FAILURE);
		} else { // there's something going on
			if(FD_ISSET(sockl, &socks)) { // check for new connections
				int connection = accept(sockl, NULL, NULL);
				if(connection < 0) {
					printf("error with accept()\n");
					exit(EXIT_FAILURE);
				}
				if(clients.size() < 3) {
					clients.push_back(new Client(connection));
					if(write(connection, "Welcome to playground!\n", 23) < 0) {
						printf("error sending message");
						clients.pop_back();
					} else
						printf("new connection on socket %d\n",
								clients[clients.size()-1]->sockc);
				} else {
					printf("warning: client list full!\n");
				}
			} else {
				for(int i = 0; i < clients.size(); i++) {
					if(FD_ISSET(clients[i]->sockc, &socks)) {
						if(read(clients[i]->sockc, buffer,
								BUFFER_SIZE) < 0) {
							printf("connection lost: fd=%d\n",
									clients[i]->sockc);
							close(clients[i]->sockc);
							clients.erase(clients.begin()+i);
						} else {
							char msg[] = "thanks!\n";
							/* MSG_NOSIGNAL is to ignore the SIGPIPE signal that
							 * would kill the process, if there's a send() error
							 * (it's the default behaviour, God knows why)
							 */
							int sent = send(clients[i]->sockc, msg, 8,
									MSG_NOSIGNAL);
							if(sent < 0) {
								printf("connection lost: fd=%d\n",
										clients[i]->sockc);
								close(clients[i]->sockc);
								clients.erase(clients.begin()+i);
							} else {
								printf("received: %s\n", buffer);
								if(strstr(buffer, "term") == buffer) {
									printf("received shutdown signal\n");
									shut_down = true;
								}
							}
						}
					}
				}
			}
		}
		//sleep(0.5);
	}
	close(sockl);
	//shutdown(sockl, 2);
}
