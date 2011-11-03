/* This class serves as a "data delivery system" between the UI and the network
 * layer. Alerts can be set and requested from each other without *knowing* each
 * other.
 */

#ifndef _DATA_HANDLER_H_
#define _DATA_HANDLER_H_

#include <eyva.h>

#include <cstring>

class DataHandler {
	public:
		DataHandler(void);
		~DataHandler(void);
		void setUITask(char const* command, size_t command_len);
		void setNetworkTask(char const* command, size_t command_len);
		size_t getUITask(char* command);
		size_t getNetworkTask(char* command);
		bool getTermSignal(void);
		void setTermSignal(void);
	
	private:
		char ui_task[BUFFER_SIZE];
		char network_task[BUFFER_SIZE];
		size_t ui_task_len;
		size_t network_task_len;
		bool term_signal;
};

#endif

