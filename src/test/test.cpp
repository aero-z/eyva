#include <utils/file_handler.h>
#include <cstring>

int main(int argc, char** argv) {
	if(argc < 3) {
		printf("syntax: [file] [id]\n");
		return -1;
	}

	bool flag;
	FileHandler f(argv[1], &flag);
	if(!flag) {
		printf("problem opening file\n");
		return -1;
	}
	int success;
	int id = aton(argv[2], 10);

	// name field
	char name[64];
	success = f.getName(name, id, 64);
	if(success == 0) {
		printf("name: none\n");
	} else {
		printf("name: %s\n", name);
	}

	// name field
	char rules[64];
	success = f.getRules(rules, id, 64);
	if(success == 0) {
		printf("rules: none\n");
	} else {
		printf("rules: %s\n", rules);
	}

	printf("------------\n");

	// message field
	char msg[64];
	success = f.getEffect(msg, id, 64);
	if(success <= 0) {
		printf("effect: none\n");
	} else {
		printf("effect: ");
		for(int i = 0; i < success; i++)
			printf("[%d]", msg[i]);
		printf("\n");
	}

	// trigger field
	char trigger[64];
	success = f.getTrigger(trigger, id, 64);
	if(success <= 0) {
		printf("trigger: none\n");
	} else {
		printf("trigger: ");
		for(int i = 0; i < success; i++)
			printf("[%d]", trigger[i]);
		printf("\n");
	}

	// value field
	success = f.getValue(id);
	printf("value: %d\n", success);

	// inventory field
	std::vector<int> inventory;
	success = f.getInventory(&inventory, id);
	if(success < 1) {
		printf("inventory: none\n");
	} else {
		printf("inventory: ");
		for(size_t i = 0; i < inventory.size(); i++)
			printf("[%d]", inventory[i]);
		printf("\n");
	}

	// characters field
	std::vector<int> characters;
	success = f.getCharacters(&characters, id);
	if(success < 1) {
		printf("characters: none\n");
	} else {
		printf("characters: ");
		for(size_t i = 0; i < characters.size(); i++)
			printf("[%d]", characters[i]);
		printf("\n");
	}
}

