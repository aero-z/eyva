/*
 * EYVA - data manipulation collection
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

#include "ayestring.h"

/**
 * Determine the length of a message according to the eyva protocol. Note that
 * this method won't count the trailing 0, and note as well that it will not
 * return the size of the message _body_ but of the _complete_ message (it's
 * a replacement for strlen()).
 * @param msg The message of which the line shall be determined.
 * @return    The size of the message.
 */
size_t
AyeString::msglen(char const* msg)
{
	// little endian:
	return (256*msg[3] + msg[2] + 4);
}

/**
 * Create a string representation of an IPv4 address.
 * @param str  The C string where the string representation of the IPv4 address
 *             will be written to.
 * @param ipv4 A pointer to the first byte where the IPv4 address is stored.
 *             This function will take that byte and the three following bytes
 *             as value.
 * @return     The size of the IP address' string representation.
 */
size_t
AyeString::iptoa(char* str, char const* ip)
{
	size_t len = 11; // start at "all numbers are <100"
	for(char* i = (char*)ip; i < ip+4; i++) {
		len += ((unsigned int)ip[(int)(i-ip)] > 99) ? 1 : 0;
	}
	sprintf(str, "%d.%d.%d.%d%c", ip[0], ip[1], ip[2], ip[3], 0);
	return len;
}

/**
 * Turn a little endian value into an integer value.
 * @param port The port (little endian).
 * @return     The port as integer.
 */
int
AyeString::porttoi(char* port)
{
	return(port[0] + 256*port[1]);
}

/**
 * Extract the numeric value from a string.
 * @param str  The string containing the value.
 * @param base The base in which the number is represented. It must be >1 and
 *             <36. In all bases, preceding whitespaces (space, tab,
 *             newline) will be ignored. For values in hex (base=16), a
 *             preceding "0x" will be ignored; however, preceding signs (-,+)
 *             also will be ignored in such case.
 * @return     The value. It will also be 0 if the string is malformed.
 */
int
AyeString::aton(char const* str, int base)
{
	int buffer;
	int start = 0;
	int length = 0;
	bool negative = false;
	bool preceding = true;
	for(size_t i = 0; i < strlen(str); i++) {
		// ignore whitespaces if preceding:
		if((str[i] == 32 || str[i] == 9 || str[i] == 10) && preceding)
			continue;

		// adjust negative flag if preceding and stop preceding:
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

		// get the one-byte-value and store if valid:
		buffer = cton(str[i], base);
		if(buffer == -1)
			break;
		
		if(preceding) {
			preceding = false;
			start = i;
		}
		length++;
	}

	// after copying, check number size (supposed to be malformed if negative):
	if(length == 0)
		return 0;
	
	// sum up and adjust negative flag:
	int sum = 0;
	for(int i = start+length-1; i >= start; i--)
		sum += (cton(str[i], base))*pow(base, start+length-1-i);
	return negative ? -sum : sum;
}

/**
 * @param base The number to be powered up.
 * @param exp  The exponent.
 * TODO negative exponents
 */
int
AyeString::pow(int base, int exp)
{
	int result = 1;
	for(int i = 0; i < exp; i++)
		result *= base;
	
	return result;
}

/**
 * Extract the numeric value from a character (don't confuse with aton!).
 * @param chr  The character for which the value is required.
 * @param base The base.
 * @return     The character's value. If the character is not defined for the
 *             base, -1 is returned.
 */
int
AyeString::cton(char const chr, int base)
{
	int val;

	// get symbol values:
	if(chr >= 48 && chr <= 59)       // ciphers
		val = chr-48;
	else if(chr >= 65 && chr <= 90)  // uppercase letters
		val = chr-55;
	else if(chr >= 97 && chr <= 122) // lowercase letters
		val = chr-87;
	else                             // invalid
		val = -1;

	// check if in base range:
	if(val < 0 || val >= base)
		val = -1;
	
	return val;
}

