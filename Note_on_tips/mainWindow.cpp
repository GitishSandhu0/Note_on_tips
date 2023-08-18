#include <iostream>
#include "window.h"

int main() {
	std::cout << "Creating Window\n";

	Window* pWindow = new Window();
	bool running = true;
	while (running) {
		if (!pWindow->processMessages()) {
			std::cout << "Closing Window\n";
			running = false;
		}

		Sleep(10);
	}

	delete pWindow;

	return 0;
}