# -c means: create object files instead of executables
# -I means: headers being in that directory can be included with <blabla>
# -g means: binaries are stuffed with additional information, for debugging
CC = g++
CFLAGS = -c -g -Wall -I/usr/include/SDL -Isrc -D_GNU_SOURCE=1 -D_REENTRANT
SERVER_LDFLAGS = 
CLIENT_LDFLAGS = -L/usr/lib -lSDL -lpthread

GENERIC_SOURCES = $(wildcard src/generic/*.cpp) $(wildcard src/generic/*/*.cpp)
SERVER_SOURCES = $(wildcard src/server/*.cpp)
CLIENT_SOURCES = $(wildcard src/client/*.cpp) $(wildcard src/client/*/*.cpp)

GENERIC_HEADERS = $(wildcard src/shared/*.h) $(wildcard src/shared/*/*.h)
SERVER_HEADERS = $(wildcard src/server/*.h)
CLIENT_HEADERS = $(wildcard src/client/*.h) $(wildcard src/client/*/*.h)

SERVER_OBJECTS = $(SERVER_SOURCES:.cpp=.o) $(GENERIC_SOURCES:.cpp=.o)
CLIENT_OBJECTS = $(CLIENT_SOURCES:.cpp=.o) $(GENERIC_SOURCES:.cpp=.o)

SERVER_EXECUTABLE = eserver
CLIENT_EXECUTABLE = eclient

SHELL = /bin/bash

all: $(GENERIC_SOURCES) $(SERVER_SOURCES) $(CLIENT_SOURCES) $(GENERIC_HEADERS) $(SERVER_HEADERS) $(CLIENT_HEADERS) $(SERVER_EXECUTABLE) $(CLIENT_EXECUTABLE)
                
$(SERVER_EXECUTABLE): $(GENERIC_HEADERS) $(SERVER_HEADERS) $(SERVER_OBJECTS)
	$(CC) $(SERVER_LDFLAGS) $(SERVER_OBJECTS) -o $@

$(CLIENT_EXECUTABLE): $(GENERIC_HEADERS) $(CLIENT_HEADERS) $(CLIENT_OBJECTS)
	$(CC) $(CLIENT_LDFLAGS) $(CLIENT_OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

keymap: src/meta/keymap.cpp
	g++ -lncurses src/meta/keymap.cpp -o keymap

clean:
	rm -f $(SERVER_OBJECTS) $(CLIENT_OBJECTS) valgrind.log

purge: clean
	rm -f $(SERVER_EXECUTABLE) $(CLIENT_EXECUTABLE) keymap

