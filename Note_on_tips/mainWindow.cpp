#include <iostream>
#include "Window.h"
#include <Windows.h>


int main() {
    std::cout << "Creating Window\n";

    Window* pWindow = new Window();
    Window::g_keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, Window::KeyboardHookCallback, GetModuleHandle(NULL), 0);

    if (pWindow) {
        HWND buttonHWND = pWindow->GetButtonHWND();
        if (buttonHWND) {
            HWND GetButtonHWND();
        }

        bool running = true;
        while (running)
        {
            running = pWindow->processMessages();

            MSG inputMsg = {};
            while (PeekMessage(&inputMsg, NULL, 0u, 0u, PM_REMOVE))
            {
                TranslateMessage(&inputMsg);
                DispatchMessage(&inputMsg);
            }

            Sleep(10);
        }

        UnhookWindowsHookEx(Window::g_keyboardHook);
        delete pWindow;
    }
    else {
        std::cerr << "Failed to create the Window object." << std::endl;
    }

    return 0;
}