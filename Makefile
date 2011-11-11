# -c means: create object files instead of executables
# -I means: headers being in that directory can be included with <blabla>
# -g means: binaries are stuffed with additional information, for debugging
CC = g++
CFLAGS = -c -g -Wall -Isrc
SERVER_LDFLAGS = 
CLIENT_LDFLAGS = -lncursesw

HYBRID_SOURCES = $(wildcard src/utils/*.cpp) $(wildcard src/hybrid/*.cpp)
SERVER_SOURCES = $(wildcard src/server/*.cpp)
CLIENT_SOURCES = $(wildcard src/client/*.cpp) $(wildcard src/client/ui/*.cpp)

HYBRID_HEADERS = $(wildcard src/utils/*.h) $(wildcard src/hybrid/*.h)
SERVER_HEADERS = $(wildcard src/server/*.h)
CLIENT_HEADERS = $(wildcard src/client/*.h) $(wildcard src/client/ui/*.h)

SERVER_OBJECTS = $(SERVER_SOURCES:.cpp=.o) $(HYBRID_SOURCES:.cpp=.o)
CLIENT_OBJECTS = $(CLIENT_SOURCES:.cpp=.o) $(HYBRID_SOURCES:.cpp=.o)

SERVER_EXECUTABLE = eserver
CLIENT_EXECUTABLE = eclient

SHELL = /bin/bash

all: $(SERVER_SOURCES) $(CLIENT_SOURCES) $(HYBRID_SOURCES) $(SERVER_HEADERS) $(CLIENT_HEADERS) $(HYBRID_HEADERS) $(SERVER_EXECUTABLE) $(CLIENT_EXECUTABLE)
                
$(SERVER_EXECUTABLE): $(SERVER_HEADERS) $(HYBRID_HEADERS) $(SERVER_OBJECTS)
	$(CC) $(SERVER_LDFLAGS) $(SERVER_OBJECTS) -o $@

$(CLIENT_EXECUTABLE): $(CLIENT_HEADERS) $(HYBRID_HEADERS) $(CLIENT_OBJECTS)
	$(CC) $(CLIENT_LDFLAGS) $(CLIENT_OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

keymap:
	g++ -lncurses src/meta/keymap.cpp -o keymap

clean:
	rm -f $(SERVER_OBJECTS) $(CLIENT_OBJECTS)

