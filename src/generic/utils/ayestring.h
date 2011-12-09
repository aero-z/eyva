/*
 * `eyva' - String manipulation collection.
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

#ifndef _AYESTRING_H_
#define _AYESTRING_H_

// Hybrid:
#include <generic/variables.h>

// Others:
#include <cstring>
#include <cstdio>
#include <vector>

namespace
AyeString
{
	extern size_t msglen(char const* msg);
	extern size_t iptoa(char* str, char const* ipv4);
	extern int porttoi(char* port);
	extern int aton(char const* str, int base);
	extern int pow(int base, int exp);
	extern int cton(char const chr, int base);
};

#endif

