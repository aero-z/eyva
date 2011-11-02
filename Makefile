# -c means: create object files instead of executables
# -I means: headers being in that directory can be included with <blabla>
CC = g++
CFLAGS = -c -Wall -Isrc/utils
LDFLAGS = -lncurses
SERVER_SOURCES = $(wildcard src/server/*.cpp) $(wildcard src/utils/*.cpp)
CLIENT_SOURCES = $(wildcard src/client/*.cpp) $(wildcard src/client/ui/*.cpp) $(wildcard src/utils/*.cpp)
SERVER_HEADER = $(wildcard src/server/*.h) $(wildcard src/utils/*.h)
CLIENT_HEADER = $(wildcard src/client/*.h) $(wildcard src/utils/*.h)
SERVER_OBJECTS = $(SERVER_SOURCES:.cpp=.o)
CLIENT_OBJECTS = $(CLIENT_SOURCES:.cpp=.o)
SERVER_EXECUTABLE = eyva-server
CLIENT_EXECUTABLE = eyva-client
SHELL = /bin/bash

all: $(SERVER_SOURCES) $(CLIENT_SOURCES) $(SERVER_EXECUTABLE) $(CLIENT_EXECUTABLE)
                
$(SERVER_EXECUTABLE): $(SERVER_OBJECTS) $(SERVER_HEADER)
	$(CC) $(LDFLAGS) $(SERVER_OBJECTS) -o $@

$(CLIENT_EXECUTABLE): $(CLIENT_OBJECTS) $(CLIENT_HEADER)
	$(CC) $(LDFLAGS) $(CLIENT_OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(SERVER_OBJECTS) $(CLIENT_OBJECTS) $(SERVER_EXECUTABLE) $(CLIENT_EXECUTABLE) valgrind.log

