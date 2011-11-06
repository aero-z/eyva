#ifndef _DATA_HANDLER_H_
#define _DATA_HANDLER_H_

#include "user.h"
#include "client.h"
#include <eyva.h>

#include <vector>     // for the list of users, and for manipulating the clients

class
DataHandler
{
	public:
		DataHandler(void);
		~DataHandler(void);
		void setGameTask(char const* command, size_t command_len,
				Client* source);
		void setNetworkTask(char const* command, size_t command_len,
				std::vector<Client*>* targets);
		size_t getGameTask(char* command, Client* source);
		size_t getNetworkTask(char* command, std::vector<Client*>* targets);
		bool getTermSignal(void);
		void setTermSignal(void);
		bool disconnect(int id);
	
	private:
		char game_task[BUFFER_SIZE];
		char network_task[BUFFER_SIZE];
		size_t game_task_len;
		size_t network_task_len;
		bool term_signal;
};

#endif

