#include "data_guard.h"

DataGuard::DataGuard(void) {
	ui = new NCursesUI();
}

DataGuard::~DataGuard(void) {
	delete ui;
}

/* PUBLIC METHODS */

void DataGuard::process(char* output_buffer, char const* input_buffer) {
	// TODO
}

