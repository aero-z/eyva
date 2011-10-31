#ifndef _MAIN_H_
#define _MAIN_H_

#include "session.h"
#include <ayelog.h>
#include <exception.h>

#define CLIENT_VERSION 0.1
#define UPDATE 0

Session* session;

void cleanUp(void);
int main(int argc, char** argv);

#endif

