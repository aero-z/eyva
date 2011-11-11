#ifndef _MAP_H_
#define _MAP_H_

// Parent Class:
#include "window.h"

// Client:
#include "../game.h"

class
Map : public Window
{
	public:
		Map(Game* game, int xpos, int ypos, int width, int height);
		~Map(void);
		/*virtual*/ bool process(int input);
		/*virtual*/ void focusWindow(void);
		/*virtual*/ bool unfocusWindow(void);
	
	private:
		Game* game;
};

#endif

