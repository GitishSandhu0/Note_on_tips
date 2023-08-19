#include <iostream>
#include "Window.h"
#include <Windows.h>


int main() {
	std::cout << "Creating Window\n";

	HHOOK g_keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookCallback, GetModuleHandle(NULL), 0);

	Window* pWindow = new Window();
	bool running = true;
    while (running)
    {
        running = pWindow->processMessages();
        Sleep(10);
    }

	delete pWindow;

	return 0;
}