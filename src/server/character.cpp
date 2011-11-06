#include "character.h"

/**
 * Constructor.
 */
Character::Character(char const* name)
{
	this->name = new char[strlen(name)+1]; // +1 for \0
	strcpy(this->name, name);
}

/**
 * Destructor.
 */
Character::~Character(void)
{
	for(size_t i = 0; i < objects.size(); i++) {
		// TODO save
		delete objects[i];
		objects.erase(objects.begin()+i);
	}

	/* Against memory leaks:
	 */
	delete[] name;
	name = NULL;
}

/* PUBLIC METHODS */

/**
 * This method gets the character's name.
 * @param name A pointer to the string where the name shall be written to.
 * @return The size of the string.
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


