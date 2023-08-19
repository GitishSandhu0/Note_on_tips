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

	bool IsVisible() const;

	bool processMessages();

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	bool m_isVisible = false;

};

