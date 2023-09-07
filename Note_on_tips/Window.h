#pragma once

#include <iostream>
#include <Windows.h>
#include <commctrl.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	Window();
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();

	HWND GetButtonHWND() const;
	std::wstring GetInputText() const;
	HWND m_hButton;

	void ShowAtCursor();
	void ToggleWindowVisibility();

	bool processMessages();
	bool windowHidden = true;

	static LRESULT CALLBACK KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam);
	static HHOOK g_keyboardHook;


private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	HWND m_hTextInput;
	
	HWND* m_pButtonHWND;


	HWND GetTextInputHWND() const;
	std::wstring m_inputText;

	static Window* s_Instance;
	static LRESULT CALLBACK TextInputProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
	void CreateTextInputAndButton();
};