#include "ui.h"
#include "exception.h"

#include <cstdio>

int
main(int argc, char** argv)
{
	UI* ui;
	try {
		ui = new UI();
	} catch(Exception* e) {
		printf("Error while initialising UI: %s\n", e->str());
		return -1;
	}
	ui->loop();
	delete ui;
}

