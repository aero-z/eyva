#include "ayestring.h"

/**
 * This function copies the first line.
 * @param dst The C string where the copied first line shall be written to.
 * @param src The C string from where the first line shall be copied from. The
 *            string is copied until the first appearance of a newline or \0
 *            (string end).
 * @return    The size of the copied string (first line).
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
 * @param msg The message of which the line shall be determined.
 * @return    The size of the message.
 */
size_t
msglen(char const* msg)
{
	/* little endian:
	 */
	return (256*msg[MESSAGE_HEAD_SIZE-1] + msg[MESSAGE_HEAD_SIZE-2]
			+ MESSAGE_HEAD_SIZE);
}

/**
 * This function will create a string representation of an IPv4 address.
 * @param str  The C string where the string representation of the IPv4 address
 *             will be written to.
 * @param ipv4 A pointer to the first byte where the IPv4 address is stored.
 *             This function will take that byte and the three following bytes
 *             as value.
 * @return     The size of the IP address' string representation.
 */
size_t
iptoa(char* str, char const* ip)
{
	size_t len = 11; // start at "all numbers are <100"
	for(char* i = (char*)ip; i < ip+4; i++) {
		len += ((unsigned int)ip[(int)(i-ip)] > 99) ? 1 : 0;
	}
	sprintf(str, "%d.%d.%d.%d%c", ip[0], ip[1], ip[2], ip[3], 0);
	return len;
}

/**
 * This function will turn a little endian value into an integer value.
 * @param port The port (little endian).
 * @return     The port as integer.
 */
int
porttoi(char* port)
{
	return(port[0] + 256*port[1]);
}

