#include "user.h"

/**
 * Constructor.
 * @param name The name of the user to be created.
 */
User::User(char const* name) {
	strcpy(this->name, name);
}


/* PUBLIC METHODS */

/**
 * This method provides the user's name.
 * @param name A pointer to the string where the name shall be written to.
 * @return The length of the name.
 */
size_t
User::getName(char* name) {
	strcpy(name, this->name);
	return strlen(this->name);
}

