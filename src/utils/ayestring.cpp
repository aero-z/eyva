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

/**
 * This function extracts the numeric value from a string.
 * @param str  The string containing the value.
 * @param base The base in which the number is represented. It must be >1 and
 *             <36. In all bases, preceding whitespaces (space, tab,
 *             newline) will be ignored. For values in hex (base=16), a
 *             preceding "0x" will be ignored; however, preceding signs (-,+)
 *             also will be ignored in such case.
 * @return     The value. It will also be 0 if the string is malformed.
 */
int
aton(char const* str, int base)
{
	int buffer;
	int start = 0;
	int length = 0;
	bool negative = false;
	bool preceding = true;
	for(size_t i = 0; i < strlen(str); i++) {
		/* If there's a whitespace and we're still preceding, ignore:
		 */
		if((str[i] == 32 || str[i] == 9 || str[i] == 10) && preceding)
			continue;

		/* If there's a "-" or "+", take it as the start of a number and set the
		 * negative flag appropriately:
		 */
		if((str[i] == 45 || str[i] == 43) && preceding) {
			preceding = false;
			start = i+1;
			negative = (str[i] == 45);
			continue;
		}

		/* If there's an "x" on the way, check if we're in hex and if it's the
		 * second symbol after a preceding "0".
		 * NOTE: So this would actually treat a sequence like "0x0x0x0x0x45" as
		 *       valid. But honestly, who would do that?
		 */
		if((str[i] == 120) && base == 16 && length == 1 && str[i-1] == 48) {
			length = 0;
			preceding = true;
			continue;
		}

		/* Otherwise, check the value of the current sign and "register" it, if
		 * it's valid, or break if invalid:
		 */
		buffer = cton(str[i], base);
		if(buffer == -1)
			break;
		
		if(preceding) {
			preceding = false;
			start = i;
		}
		length++;
	}

	/* If the number length is zero, the string must be malformed:
	 */
	if(length == 0)
		return 0;
	
	/* Otherwise sum up:
	 */
	int sum = 0;
	for(int i = start+length-1; i >= start; i--)
		sum += (cton(str[i], base))*pow(base, start+length-1-i);
	return negative ? -sum : sum;
}

/**
 * This function implements the power function.
 * @param base The number to be powered up.
 * @param exp  The exponent.
 */
int pow(int base, int exp)
{
	// TODO negative exponents
	int result = 1;
	for(int i = 0; i < exp; i++)
		result *= base;
	
	return result;
}

/**
 * This function gets the value of a character in a given base. Not to be
 * confused with aton(), that gets the value of a STRING in a given base.
 * @param chr  The character for which the value is required.
 * @param base The base.
 * @return     The character's value. If the character is not defined for the
 *             base, -1 is returned.
 */
int
cton(char const chr, int base)
{
	int val;

	/* Ciphers:
	 */
	if(chr >= 48 && chr <= 59) {
		val = chr-48;
	}
	
	/* Uppercase letters:
	 */
	else if(chr >= 65 && chr <= 90) {
		val = chr-55;
	}

	/* Lowercase letters:
	 */
	else if(chr >= 97 && chr <= 122) {
		val = chr-87;
	}

	/* Anything else:
	 */
	else {
		val = -1;
	}

	/* Check if in base range:
	 */
	if(val < 0 || val >= base)
		val = -1;
	
	return val;
}

