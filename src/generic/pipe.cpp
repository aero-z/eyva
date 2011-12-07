/*
 * EYVA
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

#include "pipe.h"

using namespace AyeString;

Pipe::~Pipe(void)
{
	pipe.clear();
}


/* PUBLIC METHODS */


/**
 * Get the oldest message in the pipe and remove it therefrom.
 * @param buffer The buffer to copy the message to.
 * @param len    The size of the buffer.
 * @return       Number of bytes copied. 0 if the buffer is too small or the
 *               pipe is empty. In that case nothing is copied and the message
 *               is not removed from the pipe.
 */
size_t
Pipe::fetch(char* buffer, size_t len)
{
	if(pipe.empty() || len < msglen(pipe[0]))
		return 0;
	
	// copy and erase:
	memcpy(buffer, pipe[0], msglen(pipe[0]));
	pipe.erase(pipe.begin());
	return msglen(buffer);
}

/**
 * Add a new message to the pipe.
 * @param msg The message to be added.
 */
void
Pipe::push(char const* msg)
{
	char* tmp = new char[msglen(msg)];
	memcpy(tmp, msg, msglen(msg));
	pipe.push_back(tmp);
}

/**
 * Check if there are still messages in the pipe.
 * @return True if there still are, otherwise false.
 */
bool
Pipe::check(void)
{
	return !(pipe.empty());
}

