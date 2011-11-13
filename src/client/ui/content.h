#ifndef _CONTENT_H_
#define _CONTENT_H_

#include <map>
#include <utility>

class
Content
{
	public:
		Content(int width, int height);
		~Content(void);
		void set(char* symbol, int foreground, int background);
	
	private:
		std::map<int, std::map<int, char[3]>> content;
		int width;
		int height;
};

#endif

