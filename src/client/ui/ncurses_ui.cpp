#include "ncurses_ui.h"

NCursesUI::NCursesUI(void) {
	initscr();  // start ncurses mode
	wm = new NCursesWM();

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
void NCursesUI::pollInput(char* buffer_out, double timeout) {
	// TODO
}

// virtual
bool NCursesUI::prompt(char const* format, ...) {
	va_list args;                                     // access handler for args
	va_start(args, format);                           // prepare access
	vsnprintf(buffer_text, BUFFER_SIZE, format, args);// copy to buffer
	va_end(args);                                     // end access

	// TODO

	return true;
}

