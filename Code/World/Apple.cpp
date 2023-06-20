#include "Apple.h"

Apple::Apple(const Vector2u& initialPosition)
	: position(initialPosition)
{ }

Vector2u Apple::GetPosition() const
{
	return position;
}

void Apple::SetPosition(const Vector2u& newPosition)
{
	position = newPosition;
}