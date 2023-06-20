#pragma once
#include <string>
#include <Windows.h>

// class Console is a static class, that provides interface of using WinAPI
// functions on console window, such as clearing the screen, pause the application, etc.
class Console
{
public:
	enum class ColorTheme
	{
		Black_Green,
		LightAqua_Black,
		LightYellow_Purple
	};

	Console() = delete;

	// All these functions use WINAPI:

	static void StopFor(unsigned milliseconds);
	static void ResetCursorPosition();
	static void SetCursorPosition(size_t x, size_t y);
	static void HideCursor();
	static void SetWindowSize(SHORT width, SHORT height);
	static void SetFontSettings(SHORT fontSize, const std::wstring& fontName);
	static void DisableScrollBars();
	static void DisableMaximizeButton();
	static void DisableWindowResizing();
	static void SetTitle(const std::string& title);

	// Other functions:

	static void ClearScreen();
	static void PauseApplication();
	static void ChangeColorTheme(const ColorTheme& theme);

private:
	static HANDLE consoleHandle;
	static HWND consoleWindow;
};