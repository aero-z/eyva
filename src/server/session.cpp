#include "session.h"

using namespace AyeLog;

/**
 * Constructor.
 * @param id   The session ID (= socket file descriptor for this connection).
 * @param ip   The client's IP address.
 * @param pipe A pointer to where answer messages shall be stored to.
 */
Session::Session(int session_id, char const* ip, Pipe* pipe, Game* game)
{
	this->pipe = pipe;
	this->session_id = session_id;
	this->game = game;

	this->ip = new char[strlen(ip)+1]; // +1 for \0
	strncpy(this->ip, ip, strlen(ip));
	this->ip[strlen(ip)] = 0; // terminate (strncpy doesn't do that...)

	//logf(LOG_DEBUG, "> %s: new session on socket %d", ip, id);
}

/**
 * Destructor.
 */
Session::~Session(void)
{
	delete[] ip;
}


/* PUBLIC METHODS */


/**
 * This method handles a message received by the client.
 * @param message     The received message.
 * @param message_len The received message's length.
 */
void
Session::process(char const* message, size_t message_len)
{
	/* TODO
	 * This is temporary, until we've got an admin client:
	 */
	if(message_len == 3 && message[0] == ':' && message[1] == 'q'
			&& message[2] == 10) {
		char response[] = {0x00, 0x00, 0x00, 0x00};
		pipe->push(response);
		return;
	}

	/* If the message length does not correspond to the length indicated in the
	 * message, send a [0A FAIL] message back:
	 */
	if(msglen(message) != message_len) {
		char response[] = {session_id, 0x0A, 0x00, 0x00};
		pipe->push(response);
		return;
	}

	/* This is the part where the messages are checked and processed. It's quite
	 * a long piece of code, maybe we can move this out to an external file:
	 */
	bool valid = true;
	switch(message[1]) {

		/* This is the first message to be received by the client. It contains
		 * the client's software version on bytes 10-12, plus the username to
		 * log in on bytes 13+ (zero terminated).
		 */
		case 1: { // [01 CONNECT]
			valid = valid && (message[10] == VERSION_MAJOR_RELEASE);
			valid = valid && (message[11] == VERSION_MINOR_RELEASE);
			valid = valid && (message[12] == VERSION_MAJOR_PATCH);
			if(!valid) { // [51 ERROR_CLIENT_COMPATIBILITY]
				char response[] = {session_id, 0x51, 0x03, 0x00,
						VERSION_MAJOR_RELEASE, VERSION_MINOR_RELEASE,
						VERSION_MAJOR_PATCH};
				pipe->push(response);
				break;
			}
			valid = valid && ((user = new User(message+13)) != NULL);
			if(!valid) { // [50 ERROR_AURHENTICATION]
				char response[] = {session_id, 0x50, 0x00, 0x00};
				pipe->push(response);
				break;
			}
			/* OK, login was successful; send a response [12 ACCEPT_CONNECTION].
			 * TODO send message of the day
			 */
			char response[] = {session_id, 0x12, 0x00, 0x00};
			pipe->push(response);
			break;
		}

		default:
			game->process(message);
			break;
	}
}

/**
 * @return The IP of this session's client.
 */
char const*
Session::getIP(void)
{
	return ip;
}

/**
 * @return The session ID (and also socket file descriptor).
 */
int
Session::getSessionID(void)
{
	return session_id;
}

