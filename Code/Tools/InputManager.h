#pragma once

// class InputManager provides information about pressed key on Windows OS.
class InputManager
{
public:
	// Every enumerator has its own Windows code of a key.
	enum class Key
	{
		Enter      = 13,
		Escape     = 27,
		ArrowUp    = 72,
		ArrowLeft  = 75,
		ArrowRight = 77,
		ArrowDown  = 80,
		Arrow      = 224,
		None       = -1
	};

	static bool UserPressedKey();
	static Key PressedKey();

private:
	static Key pressedKey;
};