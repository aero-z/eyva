#include "data_handler.h"

DataHandler::DataHandler(void) {
	game_task[0] = 0;
	network_task[0] = 0;
	term_signal = false;
};

DataHandler::~DataHandler(void) {
	// VOID
}


/* PUBLIC METHODS */

/**
 * This method should be called by the network object to alert the game object
 * to do something.
 * @param command The command that was received by the server.
 * @param command_len The length of the command.
 */
void
DataHandler::setGameTask(char const* command, size_t command_len) {
	strncpy(game_task, command, command_len);
	game_task_len = command_len;
}

/**
 * This method should be called by the game object to alert the network object
 * to send a command to the appropriate clients.
 * @param command The command to be sent to the server.
 * @param command_len The length of the command.
 */
void
DataHandler::setNetworkTask(char const* command, size_t command_len) {
	strncpy(network_task, command, command_len);
	network_task_len = command_len;
}

/**
 * This method should be called by the game object to know what to do next.
 * @param command A pointer to where the command shall be written to.
 * @return The length of the command.
 */
size_t
DataHandler::getGameTask(char* command) {
	// TODO
	command[0] = 0;
	return game_task_len;
}

/**
 * This method should be called by the network object to know what to send to
 * the appropriate clients.
 * @param command A pointer to where the command shall be written to.
 * @param targets A pointer to a list where the clients will be stored in that
 *                shall receive the command.
 * @return The length of the command.
 */
size_t
DataHandler::getNetworkTask(char* command, std::vector<Client*>* targets) {
	// TODO
	command[0] = 0;
	return network_task_len;
}

/**
 * This method tells if the term signal was set.
 * @return TRUE if the term signal was set, otherwise FALSE.
 */
bool
DataHandler::getTermSignal(void) {
	return term_signal;
}

/**
 * This method sets the term signal that can be checked with getTermSignal()
 * (see above).
 */
void
DataHandler::setTermSignal(void) {
	term_signal = true;
}

