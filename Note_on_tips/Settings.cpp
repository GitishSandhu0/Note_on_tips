#include "Settings.h"

Settings::Settings() : m_hSettingsWnd(NULL) {
    // Register the settings window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = SettingsWndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"SettingsWindowClass";

    if (!RegisterClass(&wc)) {
        // Handle registration error
    }
}

Settings::~Settings() {
    // Unregister the settings window class
    UnregisterClass(L"SettingsWindowClass", GetModuleHandle(NULL));
}

void Settings::ShowSettingsWindow() {
    if (m_hSettingsWnd) {
        // The settings window is already open
        return;
    }

    // Create the settings window
    m_hSettingsWnd = CreateWindow(
        L"SettingsWindowClass", // Registered class name
        L"Settings",            // Window title
        WS_OVERLAPPEDWINDOW,    // Window style
        CW_USEDEFAULT,          // Initial X position
        CW_USEDEFAULT,          // Initial Y position
        400,                    // Width
        300,                    // Height
        NULL,                   // Parent window
        NULL,                   // Menu, NULL for no menu
        GetModuleHandle(NULL),  // Instance handle
        NULL                    // Additional application data
    );

    if (m_hSettingsWnd) {
        ShowWindow(m_hSettingsWnd, SW_SHOWNORMAL);
        UpdateWindow(m_hSettingsWnd);
    }
}

void Settings::HideSettingsWindow() {
    if (m_hSettingsWnd) {
        DestroyWindow(m_hSettingsWnd);
        m_hSettingsWnd = NULL;
    }
}

LRESULT CALLBACK Settings::SettingsWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CLOSE:
        // Handle the close button click by destroying the window
        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        // Post a quit message to exit the message loop
        PostQuitMessage(0);
        break;

    default:
        // Handle other messages
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}
