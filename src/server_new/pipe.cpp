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

#include "pipe.h"

using namespace AyeString;

/**
 * Constructor.
 */
Pipe::Pipe(void)
{
	// VOID
}

/** 
 * Destructor.
 */
Pipe::~Pipe(void)
{
	box.clear();
}


/* PUBLIC METHODS */


/**
 * This method gets the oldest message out of the box (FIFO).
 * The message will be removed from the box.
 * @param buf A pointer to the buffer to store the message to (buffer size
 *            should be BUFFER_SIZE).
 * @return    The size of the message.
 */
size_t
Pipe::fetch(char* buf)
{
	if(!box.empty()) {
		memcpy(buf, box[0], msglen(box[0]));
		box.erase(box.begin());
		return msglen(buf);
	}
	return 0;
}

/**
 * This method adds a message to the box (FIFO).
 * @param msg The message to be added to the box.
 */
void
Pipe::push(char const* msg)
{
	char* tmp = new char[msglen(msg)];
	memcpy(tmp, msg, msglen(msg));
	box.push_back(tmp);
}

/**
 * @return True if there are messages in the box, otherwise false.
 */
bool
Pipe::check(void)
{
	return(box.size() > 0);
}

