#include "ui.h"

using namespace AyeLog;

/**
 * Constructor.
 * The ncurses session is started here.
 * @param data_handler The data handler that is needed to communicate to the
 *                     network object, and that handles all information related
 *                     stuff.
 */
UI::UI(Postmaster* pm)
{
	logf(LOG_DEBUG, "starting ncurses UI ...");
	this->pm = pm;

	/* TODO supposed to support umlauts and the like, but doesn't work:
	 */
	setlocale(LC_ALL, "");

	initscr();      // start ncurses mode
	wm = new WM();  // our window manager

	/* Check for colors and active if available:
	 */
	if(!has_colors())
		throw new Exception("colors not supported");
	start_color();

	/* This is used to enable transparent background, but we use it to let some
	 * terminal applications (like gnome-terminal) display colors correctly:
	 */
	use_default_colors();

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
	pollNetwork();
	pollInput(timeout);
}


/* PRIVATE METHODS */


/**
 * This method checks for new network messages (postmaster).
 */
void
UI::pollNetwork(void)
{
	// TODO
}

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

