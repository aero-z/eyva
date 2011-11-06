#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <eyva.h>

#include <vector>
#include <cstring>

class
Object
{
	public:
		Object(char const* effect);
		~Object(void);
		size_t getEffect(char* effect);
		void setSource(int id);
		void setTarget(int id);
		int getSource(void);
		int getTarget(void);
	
	private:
		std::vector<Object*> content;
		char effect[BUFFER_SIZE];
		int source;
		int target;
};

#endif

