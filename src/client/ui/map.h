#ifndef _MAP_H_
#define _MAP_H_

// Parent Class:
#include "window.h"

// UI:
#include "vars.h"

// Client:
#include "../game.h"

class
Map : public Window
{
	public:
		Map(Game* game, int xpos, int ypos, int width, int height);
		~Map(void);
		/*virtual*/ WindowName process(int input);
		/*virtual*/ void focus(void);
		/*virtual*/ bool unfocus(void);
	
	private:
		Game* game;
};

#endif

