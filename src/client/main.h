#ifndef __ECLIENT
#define __ECLIENT

#include "data_handler.h"
#include "network.h"
#include "ui/ncurses_ui.h"
#include <ayelog.h>
#include <exception.h>

DataHandler* data_handler;
Network* network;
UI* ui;

int main(int argc, char** argv);
void cleanUp(void);

#endif

