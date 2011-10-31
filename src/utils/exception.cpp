#include "exception.h"

Exception::Exception(char const* format, ...) {
	va_list args;           // access handler
	va_start(args, format); // prepare access
	vsnprintf(message, BUFFER_EXCEPTION_MSG, format, args);
	va_end(args);           // end access
}


/* PUBLIC METHODS */

char const* Exception::str(void) {
	return message;
}
