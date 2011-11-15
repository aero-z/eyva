#include "game.h"

/**
 * Constructor.
 * @param pipe Required to communicate to the network.
 * @param game Handling game related data.
 */
WinGame::WinGame(Pipe* pipe, Game* game) :
		Window(0, 0, 80, 24)
{
	this->pipe = pipe;
	this->game = game;

	playground = new WinPlayground(pipe, game);
	actionbar = new WinActionbar(game);
	//infobar = new WinInfobar(game);
	
	active = playground;
	active->focus();
}

/**
 * Destructor.
 */
WinGame::~WinGame(void)
{
	delete playground;
	delete actionbar;
	//delete infobar;
}


/* PUBLIC METHODS */


/**
 * This method processes a user input key.
 * @param input The key pressed by the user.
 */
WindowName
WinGame::process(int input)
{
	/* Let the active window process the input.
	 */
	WindowName next = active->process(input);

	/* The processing above will return the name of the next window to be
	 * focussed. If the window points to itself, ignore and return:
	 */
	if(next == WINDOW_IDENTITY)
		return WINDOW_IDENTITY;
	
	/* Otherwise unfocus and check if the window shall remain persistent. If not
	 * destroy it:
	 */
	if(!active->unfocus())
		delete active;
	
	/* Check the next window. If it is not within the scope of this window
	 * wrapper, forward it back up to the window manager:
	 */
	switch(next) {
		case WINDOW_PLAYGROUND:
			active = playground;
			break;
		case WINDOW_PROMPT:
		case WINDOW_PROMPT_COMMAND:
			active = new WinPrompt(pipe);
			break;
		default:
			return next;
	}

	/* If the next window is still within the scope, focus on it and stay in
	 * this scope:
	 */
	repaint();
	active->focus();

	/* Special case: Prompt entered with ':':
	 */
	if(next == WINDOW_PROMPT_COMMAND)
		active->process(':');
	
	return WINDOW_IDENTITY;
}

/**
 * This method defines the window's behaviour when being focused.
 */
void
WinGame::focus(void)
{
	active->focus();
	repaint();
}

/**
 * This method defines the window's behaviour when being unfocused.
 * @return Persistency (true if the window shall be persistent, otherwise
 *         false).
 */
bool
WinGame::unfocus(void)
{
	return true;
}

/**
 * This method repaints the screen (incl. refresh()).
 */
void
WinGame::repaint(void)
{
	playground->repaint();
	actionbar->repaint();
	//infobar->repaint();
}

