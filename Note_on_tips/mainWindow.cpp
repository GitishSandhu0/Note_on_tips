#include <iostream>
#include "Window.h"
#include <Windows.h>


int main() {
	std::cout << "Creating Window\n";

	Window* pWindow = new Window();
	Window::g_keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, Window::KeyboardHookCallback, GetModuleHandle(NULL), 0);

	bool running = true;
    while (running)
    {
        running = pWindow->processMessages();
        Sleep(10);
    }

	UnhookWindowsHookEx(Window::g_keyboardHook);
	delete pWindow;

	return 0;
}