#pragma once

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	Window();
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();

	void ShowAtCursor();
	void ToggleWindowVisibility();

	bool processMessages();
	bool windowHidden = true;

	HHOOK g_keyboardHook = nullptr;

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	
	

};

