# -c means: create object files instead of executables
# -I means: headers being in that directory can be included with <blabla>
# -g means: binaries are stuffed with additional information, for debugging
CC = g++
CFLAGS = -c -g -Wall -Isrc
SERVER_LDFLAGS = 
CLIENT_LDFLAGS = -lncurses
TEST_LDFLAGS =

HYBRID_SOURCES = $(wildcard src/utils/*.cpp) $(wildcard src/hybrid/*.cpp)
SERVER_SOURCES = $(wildcard src/server/*.cpp)
CLIENT_SOURCES = $(wildcard src/client/*.cpp) $(wildcard src/client/ui/*.cpp)
TEST_SOURCES = $(wildcard src/test/*.cpp)

HYBRID_HEADERS = $(wildcard src/utils/*.h) $(wildcard src/hybrid/*.h)
SERVER_HEADERS = $(wildcard src/server/*.h)
CLIENT_HEADERS = $(wildcard src/client/*.h) $(wildcard src/client/ui/*.h)
TEST_HEADERS = $(wildcard src/test/*.h)

SERVER_OBJECTS = $(SERVER_SOURCES:.cpp=.o) $(HYBRID_SOURCES:.cpp=.o)
CLIENT_OBJECTS = $(CLIENT_SOURCES:.cpp=.o) $(HYBRID_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o) $(HYBRID_SOURCES:.cpp=.o)

SERVER_EXECUTABLE = eserver
CLIENT_EXECUTABLE = eclient
TEST_EXECUTABLE = etest

SHELL = /bin/bash

all: $(HYBRID_SOURCES) $(SERVER_SOURCES) $(CLIENT_SOURCES) $(TEST_SOURCES) $(HYBRID_HEADERS) $(SERVER_HEADERS) $(CLIENT_HEADERS) $(TEST_HEADERS) $(SERVER_EXECUTABLE) $(CLIENT_EXECUTABLE) $(TEST_EXECUTABLE)
                
$(SERVER_EXECUTABLE): $(HYBRID_HEADERS) $(SERVER_HEADERS) $(SERVER_OBJECTS)
	$(CC) $(SERVER_LDFLAGS) $(SERVER_OBJECTS) -o $@

$(CLIENT_EXECUTABLE): $(HYBRID_HEADERS) $(CLIENT_HEADERS) $(CLIENT_OBJECTS)
	$(CC) $(CLIENT_LDFLAGS) $(CLIENT_OBJECTS) -o $@

$(TEST_EXECUTABLE): $(HYBRID_HEADERS) $(TEST_HEADERS) $(TEST_OBJECTS)
	$(CC) $(TEST_LDFLAGS) $(TEST_OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

keymap: src/meta/keymap.cpp
	g++ -lncurses src/meta/keymap.cpp -o keymap

clean:
	rm -f $(SERVER_OBJECTS) $(CLIENT_OBJECTS) $(TEST_OBJECTS)

