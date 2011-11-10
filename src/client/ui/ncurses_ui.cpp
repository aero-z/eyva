#include "ncurses_ui.h"

using namespace AyeLog;

/**
 * Constructor.
 * The ncurses session is started here.
 * @param data_handler The data handler that is needed to communicate to the
 *                     network object, and that handles all information related
 *                     stuff.
 */
NCursesUI::NCursesUI(Postmaster* pm)
{
	logf(LOG_DEBUG, "starting ncurses UI ...");
	this->pm = pm;

	initscr();             // start ncurses mode
	wm = new NCursesWM();  // our window manager

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
	noecho();              // don't display user input
	curs_set(0);           // by default, don't display the cursor
	logf(LOG_DEBUG, "UI started");
}

/**
 * Destructor.
 * The ncurses session is stopped here in order to be able to normally go on
 * with terminal work.
 */
NCursesUI::~NCursesUI(void)
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
NCursesUI::poll(double timeout)
{
	halfdelay((int)(timeout*10));
	printw("hello!");
	refresh();
	getch();

	// TODO alert network handler
}

