#include <utils/file_handler.h>
#include <cstring>

int main(int argc, char** argv) {
	if(argc < 3) {
		return -1;
	}

	bool flag;
	FileHandler f(argv[1], &flag);
	if(!flag) {
		printf("problem opening file\n");
		return -1;
	}
	int id = aton(argv[2], 10);
	char* name = new char[64];
	int success = f.getName(name, id);
	if(success == 0) {
		printf("ID not found\n");
		return -1;
	}
	printf("%s\n", name);
}

