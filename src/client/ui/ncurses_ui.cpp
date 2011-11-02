#include "ncurses_ui.h"

NCursesUI::NCursesUI(DataHandler* data_handler) {
	this->data_handler = data_handler;

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
}

NCursesUI::~NCursesUI(void) {
	delete wm;
	endwin();   // end ncurses mode
}

/* PUBLIC METHODS */

// virtual
void NCursesUI::poll(double timeout) {
	//halfdelay((int)(timeout*10));
	mvaddch(3, 4, 'h');
	refresh();
	getch();

	// TODO
}

