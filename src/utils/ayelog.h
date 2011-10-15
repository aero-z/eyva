#ifndef _AYELOG_H_
#define _AYELOG_H_

enum log_type {
	NORMAL_LOG,
	WARNING_LOG,
	ERROR_LOG
};

namespace AyeLog {
	extern void logf(log_type, char const*, ...);
	extern int verbosity_level;
};

#endif

