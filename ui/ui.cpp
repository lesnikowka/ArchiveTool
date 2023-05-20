#include "Archiver.h"
#include "Unpacker.h"
#include <iostream>
#include "ConsoleWindow.h"



int main(int argc, char **argv) {
	ConsoleWindow* window = ConsoleWindow::getInstance();

	window->Run(argc, argv);
}

