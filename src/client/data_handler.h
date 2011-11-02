/* This class serves as a "data delivery system" between the UI and the network
 * layer. Alerts can be set and requested from each other without *knowing* each
 * other.
 */

#ifndef _DATA_HANDLER_H_
#define _DATA_HANDLER_H_

#include <eyva.h>

enum EyvaCommand {
	NULL_COMMAND,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	ACTION
};

class DataHandler {
	public:
		DataHandler(void);
		~DataHandler(void);
		void alertUI(char const* command_raw);
		void alertNetwork(EyvaCommand command);
		EyvaCommand getUITask(void);
		void getNetworkTask(char* command_raw, int* command_len);
		bool checkTermSignal(void);
	
	private:
		EyvaCommand ui_task;
		EyvaCommand network_task;
};

#endif

