#include "character.h"

/**
 * Constructor.
 *
 * @param id
 *  The character's ID that is used to determine the rest of the informations.
 */
Character::Character(int id)
{
	this->id = id;
	// TODO read savefiles for loading informations
}

/**
 * Destructor.
 */
Character::~Character(void)
{
	objects.clear();

	/* Against memory leaks:
	 */
	delete[] name;
	name = NULL;
}


/* PUBLIC METHODS */


/**
 * @param name
 *  A pointer to the string where the name shall be written to.
 * @return
 * The size of the string.
 */
size_t
Character::getName(char* name)
{
	strcpy(name, this->name);
	return strlen(this->name);
}

/**
 * @return The character's x position
 */
int
Character::getXPos(void)
{
	return xpos;
}

/**
 * @return The character's y position
 */
int
Character::getYPos(void)
{
	return ypos;
}

/**
 * @param xpos The character's x position
 */
void
Character::setXPos(int xpos)
{
	this->xpos = xpos;
}

/**
 * @param ypos The character's y position
 */
void
Character::setYPos(int ypos)
{
	this->ypos = ypos;
}


