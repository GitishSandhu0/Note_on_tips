#pragma once

#include <Windows.h>

class Settings {
public:
    Settings();
    ~Settings();

    void ShowSettingsWindow();
    void HideSettingsWindow();

private:
    HWND m_hSettingsWnd;

    static LRESULT CALLBACK SettingsWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
