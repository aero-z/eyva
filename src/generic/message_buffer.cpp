/*
 * EYVA - message buffering utility
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

#include "message_buffer.h"

MessageBuffer::MessageBuffer(void)
{
	buffer = new char[0];
	buffer_len = 0;
}

MessageBuffer::~MessageBuffer(void)
{
	delete[] buffer;
}


/* PUBLIC METHODS */


/**
 * Check if a message is complete and otherwise keep in internal message buffer.
 * @param dst If the message is complete, it is removed from the buffer and
 *            added to this vector.
 * @param msg The message to be checked.
 * @param len The message's size (the received amount of bytes).
 */
void
MessageBuffer::check(std::vector<char*>* dst, char const* msg, size_t len)
{
	// add message to buffer:
	char* buffer_new = new char[buffer_len + len];
	memcpy(buffer_new, buffer, buffer_len);  // copy old buffer
	memcpy(buffer_new + buffer_len, msg, len); // append new message
	delete[] buffer;
	buffer_len += len;
	buffer = buffer_new;

	// check for complete message:
	int msg_len = msglen(buffer);
	if(buffer_len > msg_len) {
		// if message is invalid, clear buffer (tabula rasa):
		if(buffer[msg_len] != 0) {
			delete[] buffer;
			buffer = new char[0];
			return;
		}
		// copy message part to destination and update buffer:
		char* dest = new char[msg_len];
		memcpy(tmp, buffer, msg_len);
		dst->push_back(dest);
		buffer_len -= (msg_len + 1); // remove the tailing 0, too
		buffer_new = new char[buffer_len - msg_len - 1];
		memcpy(buffer_new, buffer + msg_len + 1, buffer_len);
		delete[] buffer;
		buffer = buffer_new;
	}
}

