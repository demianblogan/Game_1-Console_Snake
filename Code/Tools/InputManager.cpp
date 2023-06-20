#include "InputManager.h"

#include <conio.h>

InputManager::Key InputManager::pressedKey = Key::None;

bool InputManager::UserPressedKey()
{
	// Function '_kbhit' returns true, is user hit any key.
	return _kbhit();
}

InputManager::Key InputManager::PressedKey()
{
	// Function '_getch' returns windows-code of the key that user
	// pressed. But if user pressed any arrow, function returns 2 codes:
	// first is arrow code, and second is arrow direction.

	pressedKey = Key(_getch());

	if (pressedKey == Key::Arrow)
		pressedKey = Key(_getch());

	return pressedKey;
}