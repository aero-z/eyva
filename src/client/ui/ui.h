/* This is an abstract class from which all UI classes must be derived.
 */

#ifndef _UI_H_
#define _UI_H_

#include <eyva.h>

#include <cstdio>   // (v)(s)(f)(n)printf
#include <cstdarg>  // va_list

class UI {
	public:
		UI(void) {};
		virtual void pollInput(char* buffer_out, double timeout) = 0;
		virtual bool prompt(char const* format, ...) = 0;
};

#endif

