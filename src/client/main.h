#ifndef __ECLIENT
#define __ECLIENT

// Client:
#include "game.h"
#include "network.h"
#include "ui/ui.h"
#include "pipe.h"

// Utils:
#include <utils/ayelog.h>

Pipe* network_pipe;
Network* network;
UI* ui;
Game* game;

int main(int argc, char** argv);

#endif

