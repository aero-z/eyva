#ifndef __ECLIENT
#define __ECLIENT

// Client:
#include "game.h"
#include "pipe.h"
#include "network.h"
#include "ui/ui.h"

// Utils:
#include <utils/ayelog.h>

Pipe* pipe;
Network* network;
UI* ui;
Game* game;

int main(int argc, char** argv);

#endif

