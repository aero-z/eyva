#include "data_guard.h"

DataGuard::DataGuard(void) {
	ui = new NCursesUI();
}

DataGuard::~DataGuard(void) {
	delete ui;
}
