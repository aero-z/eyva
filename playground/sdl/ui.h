#ifndef _UI_H_
#define _UI_H_

// Utils:
#include "exception.h"

// 3rd party:
#include <SDL/SDL.h>

class
UI
{
	public:
		UI(void);
		~UI(void);
		void loop(void);
	
	private:
		void handleEvents(void);
		void handleData(void);
		void render(void);

		SDL_Event* event;
		SDL_Surface* screen;
		SDL_Surface* image;
		SDL_Rect* image_pos;
		Uint8* keys;
		bool term_signal;
		int xpos_new, ypos_new;
		int xpos, ypos;
};

#endif

