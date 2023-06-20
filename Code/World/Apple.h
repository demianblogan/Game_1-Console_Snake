#pragma once
#include "../Tools/Vector2.h"

class Apple
{
public:
	Apple(const Vector2u& initialPosition);

	Vector2u GetPosition() const;
	void SetPosition(const Vector2u& newPosition);

private:
	Vector2u position;
};