#pragma once

#include <iostream>
#include <Windows.h>
#include <commctrl.h>
#include <fstream>
#include <string>


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	Window();
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();

	std::wstring GetInputText() const;

	void ShowAtCursor();
	void ToggleWindowVisibility();

	bool processMessages();

	bool windowHidden = true;

	static LRESULT CALLBACK KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam);
	static HHOOK g_keyboardHook;

	std::wstring m_savedText;
	std::wstring GetSavedText() const;

	void SaveNoteToCSV(const std::wstring& note) const;

	HICON m_hAppIcon = (HICON)LoadImage(NULL, L"icon_light.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);


private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	HWND m_hTextInput;

	HWND GetTextInputHWND() const;
	std::wstring m_inputText;

	static Window* s_Instance;
	static LRESULT CALLBACK TextInputProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
	void CreateTextInputAndButton();
};