#pragma once

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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

	static LRESULT CALLBACK KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam);
	static HHOOK g_keyboardHook;

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	static Window* s_Instance;

};

