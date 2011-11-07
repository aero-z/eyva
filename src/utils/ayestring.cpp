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
size_t strcpy_fl(char* dest, char const* src) {
	size_t to_copy = (strstr(src, "\0")-src < strlen(src))
			? strstr(src, "\0") : strlen(src);
	strncpy(dest, src, to_copy);
	return to_copy;
}

