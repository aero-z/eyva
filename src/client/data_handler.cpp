#include "data_handler.h"

DataHandler::DataHandler(void) {
	ui_task = NULL_COMMAND;
	network_task = NULL_COMMAND;
}

DataHandler::~DataHandler(void) {
	// VOID
}

/* PUBLIC METHODS */

void DataHandler::alertUI(char const* command_raw) {
	// TODO
}

void DataHandler::alertNetwork(EyvaCommand command) {
	network_task = command;
}

EyvaCommand DataHandler::getUITask(void) {
	return ui_task;
}

void DataHandler::getNetworkTask(char* command_raw, int* command_len) {
	switch(network_task) {
		case NULL_COMMAND:
			command_raw[0] = 0;
			break;
		default:
			command_raw[0] = 1;
			break;
	}
}

bool DataHandler::checkTermSignal(void) {
	return false;
}

