#ifndef _AYELOG_H_
#define _AYELOG_H_

#include <cstdio>   // (v)(s)(f)(n)printf
#include <cstdarg>  // va_list
#include <ctime>    // struct tm

#define LOG_BUF 80  // 80 is recommended, since it's the default termial width

/**
 * These enums will be used to define the type of the log message.
 */
enum
log_type
{
	LOG_NORMAL,
	LOG_DEBUG,
	LOG_WARNING,
	LOG_ERROR
};

namespace
AyeLog
{
	extern void logf(log_type type, char const* format, ...);
	extern int log_verbosity;
};

#endif

