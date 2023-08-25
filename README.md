# Notes Taking Widget with Win32 API

The **Notes Taking Widget** is a Windows application built using the Win32 API that provides a simple way to take notes. It creates a resizable and movable window where users can quickly jot down their thoughts. The widget can be toggled using a keyboard shortcut (`Ctrl + I`).

## Features

- Create a resizable and movable notes window.
- Toggle the visibility of the notes window using the keyboard shortcut `Ctrl + I`.
- The notes window remains on top of other windows (`WS_EX_TOPMOST` style).

## Getting Started

### Prerequisites

This application requires a Windows operating system to run.

### Installation

1. Clone or download the repository to your local machine.
2. Open the project in a compatible C++ development environment (e.g., Visual Studio).

### Usage

1. Build and run the application.
2. The notes widget window will appear.
3. To show or hide the notes window, press `Ctrl + I`.
4. You can move the notes window by clicking and dragging its title bar.
5. Resize the notes window by dragging its edges.

## Code Structure

- `Window.h` - Header file for the `Window` class that manages the notes window.
- `Window.cpp` - Implementation of the `Window` class, including window creation, message processing, and keyboard hook.
- `mainWindow.cpp` - Entry point of the application, where the `Window` class is instantiated and the main loop is run.

## Class Overview

### `Window` Class

The `Window` class manages the notes widget's behavior and appearance.

**Constructor:** Initializes the window class and creates the main notes window.

**Methods:**

- `ShowAtCursor()`: Positions the window at the current cursor position.
- `ToggleWindowVisibility()`: Shows or hides the window based on its current visibility state.
- `processMessages()`: Processes Windows messages and returns a boolean indicating whether the application should continue running.

**Static Methods:**

- `KeyboardHookCallback()`: Handles keyboard hook events, specifically toggling the widget's visibility when `Ctrl + I` is pressed.

**Member Variables:**

- `m_hInstance`: Handle to the instance of the application.
- `m_hWnd`: Handle to the main notes window.
- `windowHidden`: Indicates whether the notes window is currently hidden.
- `g_keyboardHook`: Static member to store the keyboard hook.

## Contributing

Contributions to this project are welcome. If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
