#ifndef _DATA_GUARD_H_
#define _DATA_GUARD_H_

#include "ui/ncurses_ui.h"
#include <eyva_constants.h>

class DataGuard {
	public:
		DataGuard(void);
		~DataGuard(void);
		void process(char* buffer_out, char const* buffer_in);
	
	private:
		UI* ui;
};

#endif
