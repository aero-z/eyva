#include <utils/file_handler.h>
#include <cstring>

int main(int argc, char** argv) {
	FileHandler f("usr/users.db");
	char* name = new char[64];
	f.getName(name, 2);
	printf("%s\n", name);
}

