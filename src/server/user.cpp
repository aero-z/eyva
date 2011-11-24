#include "user.h"

/**
 * Constructor.
 * @param name The user's name that will be used to get the necessary
 * information from the users' savefile.
 */
User::User(char const* name, FileHandler* file_handler)
{
	this->file_handler = file_handler;

	/* Get the ID according to the name:
	 */
	printf("determinating ID ...\n");
	if((id = file_handler->getID(name)) == 0)
		throw new Exception("no user named '%s'", name);
	
	/* If the user exists, generate the data:
	 */
	this->name = new char[strlen(name)+1]; // +1 for \0
	strcpy(this->name, name);
}

/**
 * Destructor.
 */
User::~User(void)
{
	file_handler->save();
	delete name;
}


/* PUBLIC METHODS */

/**
 * This method provides the user's name.
 * @param name A pointer to the string where the name shall be written to.
 * @param len  The number of characters to be written (buffer size).
 * @return     The number of characters written.
 */
size_t
User::getName(char* name, size_t len)
{
	strncpy(name, this->name, len);
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

