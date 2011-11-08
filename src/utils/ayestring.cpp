#include "ayestring.h"

/**
 * This function copies the first line.
 *
 * @param dst
 *  The C string where the copied first line shall be written to.
 *
 * @param src
 *  The C string from where the first line shall be copied from. The string is
 *  copied until the first appearance of a newline or \0 (string end).
 *
 * @return
 *  The size of the copied string (first line).
 */
size_t
strcpy_fl(char* dest, char const* src)
{
	size_t to_copy = ((size_t)(strstr(src, "\0")-src) < strlen(src))
			? (size_t)(strstr(src, "\0")-src) : strlen(src);
	strncpy(dest, src, to_copy);
	return to_copy;
}

/**
 * This function determines the length of a message according to the eyva
 * protocol.
 *
 * @param msg
 *  The message of which the line shall be determined.
 *
 * @return
 *  The size of the message.
 */
size_t
msglen(char const* msg)
{
	/* little endian:
	 */
	return (msg[MESSAGE_HEAD_SIZE-1]*256 + msg[MESSAGE_HEAD_SIZE-2]);
}

