#include "exception.h"

/**
 * Constructor.
 * @param format The format string. See docs for `printf()' and the like.
 * @param ...    The format string arguments.
 */
Exception::Exception(char const* format, ...)
{
	va_list args;           // access handler
	va_start(args, format); // prepare access
	vsnprintf(message, BUFFER_EXCEPTION_MSG, format, args);
	va_end(args);           // end access
}


/* PUBLIC METHODS */

/**
 * @return The exception message.
 */
char const*
Exception::str(void)
{
	return message;
}

