#ifndef _AYESTRING_H_
#define _AYESTRING_H_

// Hybrid:
#include <hybrid/eyva.h>

// Others:
#include <cstring>
#include <cstdio>

size_t strcpy_fl(char* dst, char const* src);
size_t msglen(char const* msg);
size_t iptoa(char* str, char const* ipv4);
int porttoi(char* port);
int aton(char const* str, int base);
int pow(int base, int exp);
int cton(char const chr, int base);

#endif

