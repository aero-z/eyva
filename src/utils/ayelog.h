#ifndef _AYELOG_H_
#define _AYELOG_H_

#include <cstdio>   // (v)(s)(f)(n)printf
#include <cstdarg>  // va_list
#include <ctime>    // struct tm

#define LOG_BUF 120  // 80 is recommended, since it's the default termial width

enum log_type {
	NORMAL_LOG,
	DEBUG_LOG,
	WARNING_LOG,
	ERROR_LOG
};

namespace AyeLog {
	extern void logf(log_type, char const*, ...);
	extern int log_verbosity;
};

#endif

