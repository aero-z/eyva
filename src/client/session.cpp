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
		throw new NetworkException("socket() failed");
	
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
		throw new NetworkException("connect() failed: %s", strerror(errno));
	}
	logf(NORMAL_LOG, "Connected to %s on port %d ...", ip, port);
}

void Session::run(void) {
	// TODO

	// send
	output_buffer[0] = 'h';
	output_buffer[1] = 'e';
	output_buffer[2] = 'l';
	output_buffer[3] = 'l';
	output_buffer[4] = 'o';
	send(sockc, output_buffer, strlen(output_buffer), MSG_NOSIGNAL);

	// receive
	read(sockc, input_buffer, BUFFER_SIZE);

	// quit
	send(sockc, output_buffer, 0, MSG_NOSIGNAL);

	close(sockc);
}
