/* This is an abstract class from which all UI classes must be derived.
 */

#ifndef _UI_H_
#define _UI_H_

#include <eyva.h>

class UI {
	public:
		UI(void) {};
		virtual void poll(double timeout) = 0;
};

#endif

