#include <Windows.h>
#include "Window.h"

// Define an ID for the tray icon menu item
#define ID_TRAY_EXIT 1001

// Forward declaration of the tray icon message handler
LRESULT CALLBACK TrayIconProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

bool g_bAppRunning = true; // Global flag to control the application's main loop

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Window* pWindow = new Window();
    Window::g_keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, Window::KeyboardHookCallback, GetModuleHandle(NULL), 0);

    if (pWindow) {
        // Create a window for the tray icon message handling
        WNDCLASS wc = {};
        wc.lpfnWndProc = TrayIconProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = L"TrayIconWindowClass";

        RegisterClass(&wc);

        HWND trayIconWnd = CreateWindow(wc.lpszClassName, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, hInstance, NULL);

        NOTIFYICONDATA nid = {};
        nid.cbSize = sizeof(NOTIFYICONDATA);
        nid.hWnd = trayIconWnd;
        nid.uID = 1;
        nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
        nid.hIcon = pWindow->m_hAppIcon;
        nid.uCallbackMessage = WM_APP;
        lstrcpyn(nid.szTip, TEXT("Note on Tips"), sizeof(nid.szTip));

        Shell_NotifyIcon(NIM_ADD, &nid);

        while (g_bAppRunning)
        {
            MSG inputMsg = {};
            while (PeekMessage(&inputMsg, NULL, 0u, 0u, PM_REMOVE))
            {
                if (inputMsg.message == WM_QUIT) {
                    g_bAppRunning = false; // Terminate the application loop when receiving WM_QUIT
                }
                TranslateMessage(&inputMsg);
                DispatchMessage(&inputMsg);
            }

            // Handle other application logic here

            Sleep(10);
        }

        Shell_NotifyIcon(NIM_DELETE, &nid); // Remove the tray icon
        UnhookWindowsHookEx(Window::g_keyboardHook);
        delete pWindow;
    }
    else {
        // Handle any errors here
    }

    return 0;
}

LRESULT CALLBACK TrayIconProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_APP:
        switch (LOWORD(lParam))
        {
        case WM_RBUTTONDOWN:
        {
            // Display a context menu when right-clicking the tray icon
            POINT pt;
            GetCursorPos(&pt);
            HMENU hPopupMenu = CreatePopupMenu();
            AppendMenu(hPopupMenu, MF_STRING, ID_TRAY_EXIT, TEXT("Exit"));
            SetForegroundWindow(hWnd);
            TrackPopupMenu(hPopupMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
            PostMessage(hWnd, WM_NULL, 0, 0); // This is needed to close the menu after it's used
            DestroyMenu(hPopupMenu);
            break;
        }
        }
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_TRAY_EXIT:
            // User selected "Exit" from the tray icon menu
            // Perform cleanup and exit your application
            PostQuitMessage(0); // Signal the application to quit
            DestroyWindow(hWnd); // Close the tray icon window
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0); // Quit the application when the tray icon window is destroyed
        break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
