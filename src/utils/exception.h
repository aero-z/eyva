#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#define TXTBUF 1024

class Exception {
	public:
		Exception(char const*, ...);
		char const* str();
	private:
		char message[TXTBUF];
};

#endif

