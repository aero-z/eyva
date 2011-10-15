#include "network_exception.h"

#include <cstdio>   // (v)(s)(f)(n)printf
#include <cstdarg>  // va_list

NetworkException::NetworkException(char const* format, ...) {
	va_list args;           // access handler for args
	va_start(args, format); // prepare access according to '%' in format string
	vsnprintf(message, TXTBUF, format, args);
	va_end(args);
}

char const* NetworkException::str(void) {
	return message;
}
