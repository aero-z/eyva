#include "ayelog.h"

#include <cstdio>   // (v)(s)(f)(n)printf
#include <cstdarg>  // va_list
#include <ctime>    // struct tm

#define TXTBUF 120   // 80 is recommended, since it's the default terminal width

int AyeLog::verbosity_level = 0;

/* This basically works the same way as printf, but prints the formated string
 * to a file instead of stdout.
 * If verbosity level is >1, however, the string is also printed to stdout.
 *
 * NOTE: The length of the message should not exceed 80, since every string
 * larger than 80 characters will be trimmed to 80 characters.
 */
void AyeLog::logf(log_type type, char const* format, ...) {
	/* Handle the format string and its arguments.
	 * Credits: "spork" from the Ozzu webmaster forum:
	 * http://www.ozzu.com/cpp-tutorials/tutorial-writing-custom-printf-wrapper-function-t89166.html
	 */
	va_list args;           // access handler for args

	/* Prepare access: */
	va_start(args, format); // prepare access according to '%' in format string

	/* vsnprintf does the same as snprintf, except that it does not need a
	 * variable amount of arguments, but a "pointer" (va_list) to them:
	 */
	char b1[TXTBUF];            // buffer
	vsnprintf(b1, TXTBUF, format, args);

	/* End access: */
	va_end(args);

	/* Add additional stuff to the message: */
	char b2[TXTBUF];            // buffer
	switch(type) {
		case WARNING_LOG:
			snprintf(b2, TXTBUF, "! \e[33mwarning:\e[0m %s", b1);
			break;
		case ERROR_LOG:
			snprintf(b2, TXTBUF, "! \e[31mERROR:\e[0m %s", b1);
			break;
		default:
			snprintf(b2, TXTBUF, "  %s", b1);
			break;
	}

	char b3[TXTBUF];            // buffer
	time_t x = time(NULL);
	tm* timestamp = localtime(&x);
	snprintf(b3, TXTBUF, "\e[36m[%02d:%02d:%02d]\e[0m %s",
			timestamp->tm_hour, timestamp->tm_min, timestamp->tm_sec, b2);

	// TODO write to log file

	if(verbosity_level > 0)
		printf("%s\n", b3);
}
