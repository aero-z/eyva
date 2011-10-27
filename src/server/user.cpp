#include "user.h"

User::User(char const* name) {
	strcpy(this->name, name);
}

/* PUBLIC METHODS */

char const* User::getName(void) {
	return name;
}
