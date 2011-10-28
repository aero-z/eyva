#include "data_guard.h"

DataGuard::DataGuard(void) {};

/* PUBLIC METHODS */

void DataGuard::process(char *response, char const *request,
		int RESPONSE_BUF) {
	// TODO
	response[0] = 0;
	response[1] = 'y';
	response[2] = 10;
	response[3] = 0;
}

/* PRIVATE METHODS */

