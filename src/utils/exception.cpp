#include "exception.h"

#include <cstdio>   // (v)(s)(f)(n)printf
#include <cstdarg>  // va_list

Exception::Exception(char const* format, ...) {
	/* The following steps are better described in ayelog.cpp:
	 */
	va_list args;           // access handler for args
	va_start(args, format); // prepare access according to '%' in format string
	vsnprintf(message, TXTBUF, format, args);
	va_end(args);
}

char const* Exception::str(void) {
	return message;
}
