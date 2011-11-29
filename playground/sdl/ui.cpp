#include "ui.h"

UI::UI(void)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		throw new Exception("SDL_Init failed");

	event = new SDL_Event();
	term_signal = false;

	screen = SDL_SetVideoMode(400, 260, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(screen == NULL)
		throw new Exception("Surface initialisation failed");

	xpos = 0;
	ypos = 0;

	/* Display image on screen:
	 */
	image_pos = new SDL_Rect();
	image_pos->x = xpos;
	image_pos->y = ypos;
	image = SDL_LoadBMP("smile.bmp");
	if(image == NULL)
		throw new Exception("file not found: smile.bmp");
	
	SDL_SetColorKey(image, SDL_SRCCOLORKEY,
			SDL_MapRGB(image->format, 255, 255, 255)); // make white transparent
	SDL_BlitSurface(image, NULL, screen, image_pos);

	/* Print out (with double buffering):
	 */
	SDL_Flip(screen);
}

UI::~UI(void)
{
	SDL_FreeSurface(image);
	SDL_Quit();
}


/* PUBLIC METHODS */


void
UI::loop(void)
{
	while(!term_signal) {
		while(SDL_PollEvent(event)) {
			handleEvents();
		}
		handleData();
		render();
		SDL_Delay(50);
	}
}


/* PRIVATE METHODS */


void
UI::handleEvents(void)
{
	switch(event->type) {
		case SDL_QUIT:
			term_signal = true;
			break;
	}
	keys = SDL_GetKeyState(NULL);
	if(keys[SDLK_UP]) ypos_new = ypos-20;
	if(keys[SDLK_DOWN]) ypos_new = ypos+20;
	if(keys[SDLK_RIGHT]) xpos_new = xpos+20;
	if(keys[SDLK_LEFT]) xpos_new = xpos-20;
}

void
UI::handleData(void)
{
	SDL_FillRect(screen, image_pos, SDL_MapRGB(screen->format, 0, 0, 0));
	image_pos->x = xpos_new;
	image_pos->y = ypos_new;
	xpos = xpos_new;
	ypos = ypos_new;
}

void
UI::render(void)
{
	SDL_BlitSurface(image, NULL, screen, image_pos);
	SDL_Flip(screen);
}

