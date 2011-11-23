#include "user.h"

/**
 * Constructor.
 * @param name The user's name that will be used to get the necessary
 * information from the users' savefile.
 */
User::User(char const* name)
{
	this->name = new char[strlen(name)+1]; // +1 for \0
	strcpy(this->name, name);

	FileHandler fh("usr/users.db");
	// TODO read save file for information generation
}

/**
 * Destructor.
 */
User::~User(void)
{
	// TODO
}


/* PUBLIC METHODS */

/**
 * This method provides the user's name.
 * @param name A pointer to the string where the name shall be written to.
 * @return     The size of the name.
 */
size_t
User::getName(char* name)
{
	strcpy(name, this->name);
	return strlen(this->name);
}

/**
 * @return The users's ID.
 */
int
User::getID(void)
{
	return id;
}

