#include "object.h"

/**
 * Constructor.
 */
Object::Object(char const* effect)
{
	strcpy(this->effect, effect);
}

/**
 * Destructor.
 */
Object::~Object(void)
{
	for(size_t i = 0; i < content.size(); i++) {
		// TODO save
		delete content[i];
		content.erase(content.begin()+i);
	}
}

/* PUBLIC METHODS */

/**
 * This method gets the object's effect.
 * @param effect A pointer to the string where the effect shall be written to.
 * @return The size of the effect's string.
 */
size_t
Object::getEffect(char* effect)
{
	strcpy(effect, this->effect);
	return strlen(this->effect);
}

/**
 * @param id The effect's source's ID.
 */
void
Object::setSource(int id)
{
	source = id;
}

/**
 * @param id The effect's target's ID.
 */
void
Object::setTarget(int id)
{
	target = id;
}

/**
 * @return The effect's source's ID.
 */
int
Object::getSource(void)
{
	return source;
}

/**
 * @return The effect's target's ID.
 */
int
Object::getTarget(void)
{
	return target;
}

