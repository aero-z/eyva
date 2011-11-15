#ifndef _PIPE_H_
#define _PIPE_H_

// Utilities:
#include <utils/ayestring.h>

// Others:
#include <vector>

class
Pipe
{
	public:
		Pipe(void);
		~Pipe(void);
		size_t fetch(char* msg);
		void push(char const* msg);
		bool check(void);
	
	private:
		std::vector<char const*> box;
};

#endif

