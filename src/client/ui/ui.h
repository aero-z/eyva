/* This is an abstract class from which all UI classes must be derived.
 */

#ifndef _UI_H_
#define _UI_H_

enum command {
	SEND_MOVE_UP,
	SEND_MOVE_DOWN,
	SEND_MOVE_LEFT,
	SEND_MOVE_RIGHT,
	ACTION
};

class UI {
	public:
		virtual bool pollInput(command com, double timeout) = 0;
};

#endif

