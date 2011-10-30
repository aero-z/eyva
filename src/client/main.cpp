#include "session.h"
#include <ayelog.h>
#include <network_exception.h>

#include <ncurses.h>     // for ncurses
#include <cstdlib>

#define CLIENT_VERSION 0.1
#define UPDATE 0

using namespace AyeLog;

WINDOW *w_map, *w_panel;

bool setUpCurses(void) {
	/* Create a WINDOW object for the map and the panel:
	 */
	//w_panel = newwin(2, 15, 5, 5);

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
	//keypad(w_panel, true);

	/* We won't show the cursor by default (only in panel mode):
	 */
	curs_set(0);

	/* We will block 0.1 seconds for a user input, then go on (in other words:
	 * check for network activity):
	 */

	return true;
}

int main(int argc, char **argv) {
	// TODO parse user input

	log_verbosity = 0; // no log output

	initscr();  // start ncurses
	logf(LOG_DEBUG, "setting up ncurses ...");
	if(!setUpCurses()) {
		endwin();
		logf(LOG_ERROR, "color not supported by your terminal.");
		return -1;
	}

	/*
	logf(LOG_DEBUG, "establishing session to 127.0.0.1:1251");
	Session *session;
	try {
		session = new Session("127.0.0.1", 1251);
		session->run();
	} catch(NetworkException *e) {
		logf(LOG_WARNING, "%s", e->str());
		delete session;
	}
	*/

	w_map = newwin(10, 30, 10, 20);
	printw("welcome to Eyva!");
	getch();
	halfdelay(1);  // in tenth of seconds
	do {
		//             l    r    t    b    tl   tr   bl   br
		wborder(w_map, '|', '|', '=', '-', '+', '+', '+', '+');
		//wborder(w_map, 179, 179, 205, 196, 213, 184, 192, 217);
		wrefresh(w_map);
	} while(getch() != 'c');

	curs_set(1);

	delwin(w_map);
	//delwin(w_panel);
	endwin(); // end ncurses
}
