#include "Window.h"
#include <iostream>

HHOOK g_keyboardHook = nullptr;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		KBDLLHOOKSTRUCT* pKey = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

		if (wParam == WM_KEYDOWN && pKey->vkCode == 'I' && GetAsyncKeyState(VK_CONTROL))
		{
			std::cout << "Window Visibility Toggled\n";
			Window* pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(GetForegroundWindow(), GWLP_USERDATA));
			pWindow->ToggleWindowVisibility();
		}
	}

	return CallNextHookEx(g_keyboardHook, nCode, wParam, lParam);
}



Window::Window()
	: m_hInstance(GetModuleHandle(nullptr))
{
	const wchar_t* CLASS_NAME = L"New Window";

	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc;

	RegisterClass(&wndClass);

	DWORD style = WS_EX_TOPMOST;

	int width = 640;
	int height = 100;

	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	AdjustWindowRect(&rect, style, false);

	m_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Note on Tips",
		style,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		m_hInstance,
		NULL
	);

	ShowWindow(m_hWnd, SW_SHOW);

}

Window::~Window()
{
	const wchar_t* CLASS_NAME = L"New Window";
	UnregisterClass(CLASS_NAME, m_hInstance);
}

void Window::ShowAtCursor()
{
	POINT cursorPos;
	if (GetCursorPos(&cursorPos))
	{
		SetWindowPos(m_hWnd, HWND_TOPMOST, cursorPos.x, cursorPos.y, 0, 0, SWP_NOSIZE);
		ShowWindow(m_hWnd, SW_SHOW);
	}
}

void Window::ToggleWindowVisibility()
{
	if (windowHidden) {
		ShowAtCursor();
		windowHidden = false;
	}
	else {
		ShowWindow(m_hWnd, SW_HIDE);
		windowHidden = true;
	}
}

bool Window::processMessages()
{
	MSG msg = {};
	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
	{
		if (msg.message == WM_QUIT) {
			return false;
		}

	//	if (msg.message == WM_KEYDOWN && msg.wParam == 'I' && GetAsyncKeyState(VK_CONTROL))
	//	{
	//		// Ctrl + I shortcut pressed, show the window at cursor position
	//		//ShowAtCursor();
	//	}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}