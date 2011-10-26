#ifndef _IO_EXCEPTION_H_
#define _IO_EXCEPTION_H_

#define EXCEPTION_MSG_BUF 80

class IOException {
	public:
		IOException(char const*, ...);
		char const* str();
	
	private:
		char message[EXCEPTION_MSG_BUF];
};

#endif

