#include "session.h"
#include <ayelog.h>
#include <network_exception.h>

#include <curses.h>     // for ncurses
#include <cstdlib>

#define CLIENT_VERSION 0.1
#define UPDATE 0

WINDOW *w_map, *w_panel;

bool setUpCurses(void) {
	/* Check if color output is supported, and activate, if yes, otherwise
	 * quit:
	 */
	if(!has_colors())
		return false;
	start_color();

	/* Allow transparent background (we don't need exactly that, but some
	 * terminal emulators otherwise won't display colors):
	 */
	use_default_colors();

	/* Create a WINDOW object for the map and the panel:
	 */
	w_map = initscr();
	w_panel = initscr();

	/* User input shall be handled immediately without waiting for newline. Note
	 * that ^C, ^Z and the rest still work (those would be handled if raw() was
	 * executed):
	 */
	cbreak();

	/* User input shall not be directly printed out. We'll handle that manually
	 * (e.g. arrow keys should be usable):
	 */
	noecho();

	/* We allow buttons like F1, F2 and (important!) arrow keys:
	 */
	keypad(w_map, true);
	keypad(w_panel, true);

	/* We won't show the cursor by default (only in panel mode):
	 */
	curs_set(0);

	/* We will block 0.1 seconds for a user input, then go on (in other words:
	 * check for network activity):
	 */
	halfdelay(1);  // in tenth of seconds

	return true;
}

int main(int argc, char **argv) {
	// TODO parse user input

	AyeLog::log_verbosity = 2;  // also print debug messages

	if(!setUpCurses()) {
		endwin();
		AyeLog::logf(ERROR_LOG, "color not supported by your terminal.");
		return -1;
	}

	Session *session = new Session("127.0.0.1", 1251);
	try {
		session->run();
	} catch(NetworkException *e) {
		AyeLog::logf(WARNING_LOG, "%s", e->str());
		delete session;
	}

	wprintw(w_panel, "Hello World!!!");
	refresh();
	getch();

	endwin();
}
