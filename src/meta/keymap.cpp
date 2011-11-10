//#include <cstdlib>
#include <ncurses.h>

int input;

bool inputStep(void) {
	if((input = getch()) == 'c') // if 'c' is pressed, exit
		return false;
	printw("\r%c : %d                               ", input, input);
	return true;
}

int main(int argc, char** argv) {
	initscr();              // start curses mode
	raw();                  // get the input before ENTER (=> arrow keys)
	noecho();               // don't print input (=> arrow keys)
	keypad(stdscr, true);   // enable F1, F2, ... and arrow keys
	// halfdelay();           // waits some time for input, then goes on
	curs_set(0);            // hide the cursor

	while(inputStep());

	endwin();               // stop curses mode
	return 0;
}

