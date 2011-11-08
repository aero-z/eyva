#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <hybrid/eyva.h>

#include <cstdio>   // (v)(s)(f)(n)printf
#include <cstdarg>  // va_list

class
Exception
{
	public:
		Exception(char const* format, ...);
		char const* str(void);
	
	private:
		char message[BUFFER_EXCEPTION_MSG];
};

#endif

