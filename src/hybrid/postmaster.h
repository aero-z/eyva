#ifndef _POSTMASTER_H_
#define _POSTMASTER_H_

#include <vector>

enum postbox {
	BOX_NETWORK,
	BOX_GAME,
	BOX_UI
};

class
Postmaster
{
	public:
		Postmaster(void);
		~Postmaster(void);
		getMessage(char* message, postbox box);
		sendMessage(char const* message);

	private:
		std::vector<char*> box_network;
		std::vector<char*> box_game;
		std::vector<char*> box_ui;
		postbox determinate_box(char const* message);
}

#endif

