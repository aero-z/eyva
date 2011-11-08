#ifndef __ESERVER
#define __ESERVER

#include "data_handler.h"
#include "game.h"
#include "network.h"
#include <exception.h>
#include <ayelog.h>

#include <cstdio>

DataHandler* data_handler;
Network* network;
Game* game;

void cleanUp(void);
int main(int argc, char** argv);

#endif

