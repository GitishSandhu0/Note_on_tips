#include <iostream>
#include "window.h"
#include <Windows.h>

HHOOK g_keyboardHook = nullptr;

int main() {
	std::cout << "Creating Window\n";

	Window* pWindow = new Window();
	bool running = true;
    while (running)
    {
        running = pWindow->processMessages();
        Sleep(10);
    }

	delete pWindow;

    if (g_keyboardHook)
    {
        UnhookWindowsHookEx(g_keyboardHook);
    }

	return 0;
}