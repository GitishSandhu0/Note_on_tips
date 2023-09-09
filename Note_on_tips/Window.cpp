#include "Window.h"

Window* Window::s_Instance = nullptr;

HHOOK Window::g_keyboardHook = nullptr;


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

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


LRESULT Window::KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		KBDLLHOOKSTRUCT* pKey = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

		if (wParam == WM_KEYDOWN && pKey->vkCode == 'Q' && GetAsyncKeyState(VK_CONTROL))
		{
			if (s_Instance && s_Instance->g_keyboardHook)
			{
				s_Instance->ToggleWindowVisibility();
			}
		}
	}

	return CallNextHookEx(g_keyboardHook, nCode, wParam, lParam);
}


HWND Window::GetTextInputHWND() const
{
	return m_hTextInput;
}


LRESULT Window::TextInputProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch (uMsg)
	{

	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
		{
			std::cout << "Enter Btn Pressed\n";
			int textLength = GetWindowTextLength(s_Instance->m_hTextInput);

			if (textLength > 0)
			{
				std::wstring textBuffer(textLength + 1, L'\0');
				GetWindowText(s_Instance->m_hTextInput, &textBuffer[0], textLength + 1);
				s_Instance->m_savedText = textBuffer;

				s_Instance->SaveNoteToCSV(textBuffer);

				SetWindowText(s_Instance->m_hTextInput, L"");

			}
		}
		break;
	}

	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}




void Window::CreateTextInputAndButton()
{
	{
		m_hTextInput = CreateWindowEx(
			0,
			L"EDIT",
			L"",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			2, 2, 490, 25,
			m_hWnd,
			NULL,
			m_hInstance,
			NULL
		);

		SetWindowSubclass(m_hTextInput, TextInputProc, 0, 0);

	}

}


Window::Window()
{
	m_hInstance = GetModuleHandle(NULL);

	const wchar_t* CLASS_NAME = L"New Window";

	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc;

	RegisterClass(&wndClass);

	DWORD style = WS_EX_TOPMOST;

	int width = 510;
	int height = 70;

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

	SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

	CreateTextInputAndButton();

	s_Instance = this;

	m_inputText = L"";

	ShowWindow(m_hWnd, SW_HIDE);
}




Window::~Window()
{
	// Set the m_hWnd member variable to null
	m_hWnd = nullptr;

	// Destroy the keyboard hook
	UnhookWindowsHookEx(g_keyboardHook);

	// Unregister the window class
	UnregisterClass(L"New Window", m_hInstance);
}


std::wstring Window::GetInputText() const
{
	return m_inputText;
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
	std::cout << "Window Visibility Toggled \n";

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
	while (GetMessage(&msg, nullptr, 0u, 0u))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

std::wstring Window::GetSavedText() const
{
	return m_savedText;
}

void Window::SaveNoteToCSV(const std::wstring& note) const
{
	std::wofstream file("notes.csv", std::ios_base::app); // Open the CSV file in append mode
	if (file.is_open())
	{
		file << note << L"\n"; // Write the note to the file followed by a newline
		file.close(); // Close the file
		std::cout << "Note Saved\n";
	}
	else
	{
		// Handle error: Unable to open the CSV file
		MessageBox(NULL, L"Error: Unable to save note to CSV file.", L"Error", MB_ICONERROR);
	}
}
