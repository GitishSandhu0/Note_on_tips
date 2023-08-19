#include "Window.h"

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

bool Window::IsVisible() const
{
	return m_isVisible;
}

bool Window::processMessages()
{
	MSG msg = {};
	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
	{
		if (msg.message == WM_QUIT) {
			return false;
		}

		if (msg.message == WM_KEYDOWN && msg.wParam == 'I' && GetAsyncKeyState(VK_CONTROL))
		{
			// Ctrl + I shortcut pressed, show the window at cursor position
			ShowAtCursor();
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}
