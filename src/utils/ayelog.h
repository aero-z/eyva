/*
 * `eyva'
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

#ifndef _AYELOG_H_
#define _AYELOG_H_

#include <cstdio>   // (v)(s)(f)(n)printf
#include <cstdarg>  // va_list
#include <ctime>    // struct tm

#define LOG_BUF 100

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

