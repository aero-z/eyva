#include "ui.h"

UI::UI(void)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		throw new Exception("SDL_Init failed");
	
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	SDL_WM_SetCaption("eyva", "eyva");

	event = new SDL_Event();
	term_signal = false;

	screen = SDL_SetVideoMode(500, 300, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(screen == NULL)
		throw new Exception("Surface initialisation failed");

	/* Display image on screen:
	 */
	image_rect = new SDL_Rect();
	image_rect->x = 0;
	image_rect->y = 0;
	image = SDL_LoadBMP("smile.bmp");
	if(image == NULL)
		throw new Exception("file not found: smile.bmp");
	
	mouse_rect = new SDL_Rect();
	
	SDL_SetColorKey(image, SDL_SRCCOLORKEY,
			SDL_MapRGB(image->format, 255, 255, 255)); // make white transparent
	SDL_BlitSurface(image, NULL, screen, image_rect);

	/* Setup mouse:
	 */
	//SDL_ShowCursor(SDL_DISABLE);
	Uint8 data[7] = {0, 0, 0, 0, 0, 0, 0};
	Uint8 mask[7] = {0x82, 0x44, 0x28, 0x10, 0x28, 0x44, 0x82};
	cursor = SDL_CreateCursor(data, mask, 7, 7, 3, 3);
	SDL_SetCursor(cursor);

	/* Print out (with double buffering):
	 */
	SDL_Flip(screen);
}

UI::~UI(void)
{
	SDL_FreeCursor(cursor);
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
		SDL_Delay(30);
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
		case SDL_KEYDOWN:
			keys = SDL_GetKeyState(NULL);
			switch(event->key.keysym.sym) {
				case SDLK_UP:
				case SDLK_k:
					image_rect->y -= 20;
					break;
				case SDLK_DOWN:
				case SDLK_j:
					image_rect->y += 20;
					break;
				case SDLK_RIGHT:
				case SDLK_l:
					image_rect->x += 20;
					break;
				case SDLK_LEFT:
				case SDLK_h:
					image_rect->x -= 20;
					break;
				case SDLK_ESCAPE:
					term_signal = true;
					break;
				default:
					break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEMOTION: {
			int x, y;
			SDL_GetMouseState(&x, &y);
			mouse_rect->x = x;
			mouse_rect->y = y;
			// TODO
			break;
		}
		default:
			break;
	}
}

void
UI::handleData(void)
{
}

void
UI::render(void)
{
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	SDL_BlitSurface(image, NULL, screen, image_rect);
	mouse_rect->w = 20;
	mouse_rect->h = 20;
	//SDL_FillRect(screen, mouse_rect, SDL_MapRGB(screen->format, 100, 180, 50));
	SDL_Flip(screen);
}

