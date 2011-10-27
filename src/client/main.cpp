#include "session.h"

#include <ayelog.h>
#include <network_exception.h>

int main() {
	AyeLog::log_verbosity = 2;

	try {
		Session* session = new Session("127.0.0.1", 1251);
		session->run();
	} catch(NetworkException* e) {
		AyeLog::logf(WARNING_LOG, "%s", e->str());
	}
}
