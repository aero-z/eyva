#ifndef _MAIN_H_
#define _MAIN_H_

#include "server.h"
#include <exception.h>
#include <ayelog.h>

#include <cstdio>

Server* server;

void cleanUp(void);
int main(int argc, char** argv);

#endif

