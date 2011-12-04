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
#include <hybrid/eyva.h>

// Others:
#include <cstring>
#include <cstdio>
#include <vector>

namespace
AyeString
{
	size_t msglen(char const* msg);
	size_t iptoa(char* str, char const* ipv4);
	int porttoi(char* port);
	int aton(char const* str, int base);
	int pow(int base, int exp);
	int cton(char const chr, int base);
}

#endif

