#include "session.h"
#include <ayelog.h>
#include <network_exception.h>

#include <ncurses.h>     // for ncurses
#include <cstdlib>

#define CLIENT_VERSION 0.1
#define UPDATE 0

int main(int argc, char** argv) {
	AyeLog::log_verbosity = 2;  // also print debug messages

	/* Create a WINDOW object for the map and the panel:
	 */
	//WINDOW* w_map = initscr();
	WINDOW* w_panel = initscr();

	/* User input shall be handled immediately without waiting for newline:
	 */
	raw();

	try {
		Session* session = new Session("127.0.0.1", 1251);
		session->run();
	} catch(NetworkException* e) {
		AyeLog::logf(WARNING_LOG, "%s", e->str());
	}

	wprintw(w_panel, "Hello World!!!");
	refresh();
	getch();

	endwin();
}
