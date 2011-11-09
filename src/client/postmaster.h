#ifndef _POSTMASTER_H_
#define _POSTMASTER_H_

// Utils:
#include <utils/ayestring.h>

// Others:
#include <vector>
#include <cstring>
#include <cstdlib>

/**
 * This enum is used to indicate what box shall be used for an action.
 */
enum Box {
	BOX_UI,
	BOX_NETWORK
};

class
Postmaster
{
	public:
		Postmaster(void);
		~Postmaster(void);
		void send(Box box, char const* msg);
		size_t fetch(char* msg, Box box);
	
	private:
		std::vector<char*>* identify(Box box);
		std::vector<char*> box_ui;
		std::vector<char*> box_network;
};

#endif

