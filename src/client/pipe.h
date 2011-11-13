#ifndef _PIPE_H_
#define _PIPE_H_

// Utils:
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
		void add(char const* msg);
		bool check(void);
	
	private:
		std::vector<char*> box;
};

#endif

