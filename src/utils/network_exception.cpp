#include "network_exception.h"

#include <cstdio>   // (v)(s)(f)(n)printf
#include <cstdarg>  // va_list

NetworkException::NetworkException(char const* format, ...) {
	/* The following steps are better described in ayelog.cpp:
	 */
	va_list args;           // access handler for args
	va_start(args, format); // prepare access according to '%' in format string
	vsnprintf(message, EXCEPTION_MSG_BUF, format, args);
	va_end(args);
}

char const* NetworkException::str(void) {
	return message;
}
