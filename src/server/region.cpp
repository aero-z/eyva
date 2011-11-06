#include "region.h"

/**
 * Constructor.
 */
Region::Region(void)
{
	// TODO
}

/**
 * Destructor.
 */
Region::~Region(void)
{
	// TODO
}

/* PUBLIC METHODS */

/**
 * This method adds an object to a specified place.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @return Success (true if success, false if fail).
 */
bool
Region::addObject(Object* object, int x, int y)
{
	if(objects[x][y] != NULL)
		return false;

	objects[x][y] = object;
	return true;
}

/**
 * This method removes an object by pointer.
 * @param object A pointer to the object that shall be removed.
 * @return Success (true if success, false if fail).
 */
bool
Region::removeObject(Object* object)
{
	for(int x = 0; x < REGION_WIDTH; x++) {
		for(int y = 0; y < REGION_HEIGHT; y++) {
			if(objects[x][y] == object) {
				objects[x][y] = NULL;
				return true;
			}
		}
	}
	return false;
}

/**
 * This method removes an object by coordinate.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @return Success (true if success, false if fail).
 */
bool
Region::removeObject(int x, int y)
{
	if(objects[x][y] == NULL)
		return false;
	
	objects[x][y] = NULL;
	return true;
}

