#include "user.h"

/**
 * Constructor.
 * @param id The user's ID.
 */
User::User(int id)
{
	this->id= id;
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
 * @return The size of the name.
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

