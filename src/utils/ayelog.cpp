#include "ayelog.h"

/* Verbosity level for log printouts to stdout.
 * 0: no printout (only errors)
 * 1: warnings and errors
 * 2: normal printout
 * 3: debug printout (attention! development use; produces a lot of output)
 *
 * Log files are always written with log_verbosity level 2.
 */
int AyeLog::log_verbosity = 1; // default value for printout

/**
 * This function basically works the same way as printf, but prints the formated
 * string also to a file.
 * NOTE: The length of the message should not exceed 80, since every string
 * larger than 80 characters will be trimmed to 80 characters.
 * @param type   The log type; can be LOG_ERROR, LOG_WARNING, LOG_NORMAL or
 *               LOG_DEBUG.
 * @param format The format string.
 * @param ...    The arguments for the format string.
 */
void
AyeLog::logf(log_type type, char const* format, ...)
{
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
	char b1[LOG_BUF];            // buffer
	vsnprintf(b1, LOG_BUF, format, args);

	/* End access: */
	va_end(args);

	/* Add additional stuff to the message: */
	char b2[LOG_BUF];            // buffer
	switch(type) {
		case LOG_WARNING:
			snprintf(b2, LOG_BUF, "! \e[33mwarning:\e[0m %s", b1);
			break;
		case LOG_ERROR:
			snprintf(b2, LOG_BUF, "! \e[31mERROR:\e[0m %s", b1);
			break;
		case LOG_DEBUG:
			snprintf(b2, LOG_BUF, "  \e[36m%s\e[0m", b1);
			break;
		default:
			snprintf(b2, LOG_BUF, "  %s", b1);
			break;
	}

	char b3[LOG_BUF];            // buffer
	time_t x = time(NULL);
	tm* timestamp = localtime(&x);
	snprintf(b3, LOG_BUF, "\e[36m[%02d:%02d:%02d]\e[0m %s",
			timestamp->tm_hour, timestamp->tm_min, timestamp->tm_sec, b2);

	// TODO write to log file, ignore LOG_DEBUG

	/* Write log message to stdout, depending on log level:
	 */
	if((type == LOG_DEBUG && log_verbosity >= 3)
			|| (type == LOG_NORMAL && log_verbosity >= 2)
			|| (type == LOG_WARNING && log_verbosity >= 1)
			|| (type == LOG_ERROR))
		printf("%s\r\n", b3);
}
