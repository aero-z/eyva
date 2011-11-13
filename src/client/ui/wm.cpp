#include "wm.h"

/**
 * Constructor.
 */
WM::WM(Pipe* pipe, Game* game)
{
	this->pipe = pipe;
	this->game = game;

	/* Create windows:
	 */
	playground = new Playground(pipe, game);
	prompt = new Prompt(pipe, game);
	
	// TODO
	active = playground;

	active->focus();
}

/**
 * Destructor.
 */
WM::~WM(void)
{
	delete playground;
	delete prompt;
}


/* PUBLIC METHODS */


/**
 * This method processes a user input (button) by sending it to the currently
 * focused window.
 * @param input The key pressed by the user.
 */
void
WM::process(int input)
{
	/* Let the active window process the input:
	 */
	WindowName next = active->process(input);

	/* The processing method will return the name of the next window to be
	 * focused. If the window does not point to itself, perform a focus change:
	 */
	if(next != IDENTITY) {
		/* The unfocussing method will return false, if the window shall be
		 * destroyed:
		 */
		if(!active->unfocus())
			delete active;

		switch(next) {
			case PLAYGROUND:
				active = playground;
				break;
			case PROMPT:
			case PROMPT_COMMAND:
				active = prompt;
				break;
			default:
				break;
		}

		/* Invoke the focussing process:
		 */
		active->focus();

		/* Special case: if the prompt was entered with a ':':
		 */
		if(next == PROMPT_COMMAND)
			active->process(':');
	}
}

/**
 * This method processes a network message.
 * @param msg The eyva protocol compliant message to be processed.
 */
void
WM::process(char const* msg)
{
	// TODO animation!
}

