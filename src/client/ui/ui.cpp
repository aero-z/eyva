#include "ui.h"

using namespace AyeLog;

/**
 * Constructor.
 * The ncurses session is started here.
 * @param pipe Used to send messages to the network.
 * @param game Handles and stores game data.
 */
UI::UI(Pipe* pipe, Game* game)
{
	this->pipe = pipe;
	this->game = game;

	logf(LOG_DEBUG, "starting ncurses UI ...");
	logf(LOG_DEBUG, "maximum number of color pairs: %d", COLOR_PAIRS);

	/* TODO supposed to support umlauts and the like, but doesn't work:
	 */
	setlocale(LC_ALL, "");

	initscr();      // start ncurses mode
	wm = new WM(pipe, game);  // our window manager

	/* Set the behaviour of ncurses:
	 */
	cbreak();              // for user input, don't wait for the return
	keypad(stdscr, TRUE);  // allow arrow and F keys
	noecho();              // don't display user input
}

/**
 * Destructor.
 * The ncurses session is stopped here in order to be able to normally go on
 * with terminal work.
 */
UI::~UI(void)
{
	delete wm;
	endwin();   // end ncurses mode
}


/* PUBLIC METHODS */


/**
 * This is a method defined [virtual] by the UI superclass.
 * It checks for user input and alerts the network handler via postmaster if
 * necessary.
 * @param timeout The delay (or time to wait) for a user input before going on
 *                in seconds.
 */
void
UI::poll(double timeout)
{
	pollInput(timeout);
}

/**
 * This method processes a network message.
 * @param msg The eyva protocol conform message.
 */
void
UI::process(char const* msg)
{
	wm->process(msg);
}


/* PRIVATE METHODS */


/**
 * This method checks for user input and lets the WM handle it.
 * @param timeout The time to block on a user input polling.
 */
void
UI::pollInput(double timeout)
{
	halfdelay((int)(timeout*10));
	int input = getch();
	switch(input) {
		case ERR:
			break;
		default:
			wm->process(input);
	}
}

