#ifndef __ECLIENT
#define __ECLIENT

// Client:
#include "postmaster.h"
#include "network.h"
#include "ui/ui.h"

// Utils:
#include <utils/ayelog.h>

Postmaster* pm;
Network* network;
UI* ui;

int main(int argc, char** argv);

#endif

