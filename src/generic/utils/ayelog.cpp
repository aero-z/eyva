/*
 * EYVA - log class
 * Copyright (C) 2011 ayekat (martin.weber@epfl.ch)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ayelog.h"

/* Verbosity level for log printouts to stdout.
 * 0: no printout (only errors)
 * 1: warnings and errors (default)
 * 2: normal printout (log files)
 * 3: debug printout (lot of crap)
 */
int AyeLog::log_verbosity = 1; // default value for printout

/**
 * Set a log message.
 * @param type   Log type: LOG_ERROR, LOG_WARNING, LOG_NORMAL or LOG_DEBUG.
 * @param format Format string.
 * @param ...    Format string arguments.
 */
void
AyeLog::logf(log_type type, char const* format, ...)
{
	// process arguments:
	va_list args;           // access handler for args
	va_start(args, format); // prepare access according to '%' in format string
	char b1[LOG_BUFFER_SIZE];
	vsnprintf(b1, LOG_BUFFER_SIZE, format, args);
	va_end(args);           // end access

	// add color:
	char b2[LOG_BUFFER_SIZE];
	switch(type) {
		case LOG_WARNING:
			snprintf(b2, LOG_BUFFER_SIZE, "! \e[33mwarning:\e[0m %s", b1);
			break;
		case LOG_ERROR:
			snprintf(b2, LOG_BUFFER_SIZE, "! \e[31mERROR:\e[0m %s", b1);
			break;
		case LOG_DEBUG:
			snprintf(b2, LOG_BUFFER_SIZE, "  \e[36m%s\e[0m", b1);
			break;
		default:
			snprintf(b2, LOG_BUFFER_SIZE, "  %s", b1);
			break;
	}

	/* TODO find a way to avoid valgrind errors on this
	// add timestamp:
	char b3[LOG_BUFFER_SIZE];
	time_t rawtime;
	time(&rawtime);
	struct tm* timestamp = localtime(&rawtime);
	snprintf(b3, LOG_BUFFER_SIZE, "\e[36m[%02d:%02d:%02d]\e[0m %s",
			timestamp->tm_hour, timestamp->tm_min, timestamp->tm_sec, b2);
	*/

	// TODO write to log file

	// write to stdout, according to the log level:
	if((type == LOG_DEBUG && log_verbosity >= 3)
			|| (type == LOG_NORMAL && log_verbosity >= 2)
			|| (type == LOG_WARNING && log_verbosity >= 1)
			|| (type == LOG_ERROR))
		printf("%s\r\n", b2);
}

