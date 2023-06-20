#include "Console.h"
#include <iostream>

HANDLE Console::consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
HWND Console::consoleWindow = GetConsoleWindow();

void Console::StopFor(unsigned milliseconds)
{
	Sleep(milliseconds);
}

void Console::ResetCursorPosition()
{
	SetCursorPosition(0, 0);
}

void Console::SetCursorPosition(size_t x, size_t y)
{
	std::cout.flush();
	COORD newCursorPosition = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(consoleHandle, newCursorPosition);
}

void Console::HideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void Console::SetWindowSize(SHORT width, SHORT height)
{
	SMALL_RECT windowArea = { 0, 0, width, height };

	SetConsoleWindowInfo(consoleHandle, TRUE, &windowArea);
}

void Console::SetFontSettings(SHORT fontSize, const std::wstring& fontName)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = fontSize;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, sizeof(L"Consolas"), fontName.c_str());

	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void Console::DisableScrollBars()
{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo);
	COORD newBuffetSize =
	{
		bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1,
		bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1
	};

	SetConsoleScreenBufferSize(consoleHandle, newBuffetSize);
}

void Console::DisableMaximizeButton()
{
	DWORD windowStyle = GetWindowLong(consoleWindow, GWL_STYLE);
	windowStyle &= ~WS_MAXIMIZEBOX;
	SetWindowLong(consoleWindow, GWL_STYLE, windowStyle);
	SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
}

void Console::DisableWindowResizing()
{
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void Console::SetTitle(const std::string& title)
{
	SetConsoleTitleA(title.c_str());
}

void Console::ClearScreen()
{
	system("cls");
}

void Console::PauseApplication()
{
	system("pause");
}

void Console::ChangeColorTheme(const ColorTheme& theme)
{
	switch (theme)
	{
	case ColorTheme::Black_Green:
		system("Color 02"); // Black background, Green text
		break;
	case ColorTheme::LightAqua_Black:
		system("Color B0"); // Light Aqua background, Black text
		break;
	case ColorTheme::LightYellow_Purple:
		system("Color E5"); // Light Yellow background, Purple text
		break;
	}
}