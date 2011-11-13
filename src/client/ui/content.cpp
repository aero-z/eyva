#include "content.h"

/**
 * Constructor.
 * @param width  The number of fields in the x axis.
 * @param height The number of fields in the y axis.
 */
Content::Content(int width, int height)
{
	this->width = width;
	this->height = height;
}

/**
 * Destructor.
 */
Content::~Content(void)
{
	for(int x = 0; x < width; x++)
		for(int y = 0; y < height; y++)
			content[x].erase[y];
}


/* PUBLIC METHODS */


