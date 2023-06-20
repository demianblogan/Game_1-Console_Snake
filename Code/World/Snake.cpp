#include "Snake.h"

#include "Apple.h"
#include "Walls.h"

Snake::Snake(const Vector2u& initialPosition, const Vector2u& worldBoundaries)
	: WORLD_BOUNDARIES(worldBoundaries)
{
	bodyParts.push_back(initialPosition);
}

bool Snake::IsAlive() const
{
	return isAlive;
}

bool Snake::IsTouching(const Apple& apple) const
{
	const Vector2u& headPosition = bodyParts[0];
	const Vector2u& applePosition = apple.GetPosition();

	return headPosition == applePosition;
}

bool Snake::IsTouching(const Walls& walls) const
{
	const Vector2u& headPosition = bodyParts[0];

	const std::vector<Vector2u>& wallPositions = walls.GetWallPositions();
	size_t wallSize = wallPositions.size();

	auto foundIter = std::find_if(wallPositions.begin(), wallPositions.end(),
		[&headPosition](const Vector2u& wallPosition)
		{
			return wallPosition == headPosition;
		});

	return foundIter != wallPositions.end();
}

bool Snake::IsTouchingItself() const
{
	size_t partCount = bodyParts.size();

	// Snake can't touch itself, if its length <= 4.
	if (partCount <= 4)
		return false;

	const Vector2u& headPosition = bodyParts[0];
	for (size_t i = 4; i < partCount; i++)
		if (headPosition == bodyParts[i])
			return true;

	return false;
}

void Snake::Move(double deltaTime, bool isClassicMode)
{
	if (headDirection == Direction::None || !NeedToMove(deltaTime))
		return;

	// Move other part toward the head.
	size_t partsCount = bodyParts.size();
	for (size_t i = partsCount - 1; i >= 1; i--)
		bodyParts[i] = bodyParts[i - 1];

	// Move head onto new position.
	Vector2u& head = bodyParts[0];

	switch (headDirection)
	{
	case Direction::Up:
		head.y--;
		break;
	case Direction::Right:
		head.x++;
		break;
	case Direction::Left:
		head.x--;
		break;
	case Direction::Down:
		head.y++;
		break;
	}

	if (isClassicMode)
	{
		// If snake's head touches walls, set it on the opposite side.
		// WORLD_BOUNDARIES.x - 1 or WORLD_BOUNDARIES.y - 1 is a wall position.
		// So we need to subtract 2.

		if (head.x == 0)
			head.x = WORLD_BOUNDARIES.x - 2;
		else if (head.x == WORLD_BOUNDARIES.x - 1)
			head.x = 1;
		else if (head.y == 0)
			head.y = WORLD_BOUNDARIES.y - 2;
		else if (head.y == WORLD_BOUNDARIES.y - 1)
			head.y = 1;
	}
}

const std::vector<Vector2u>& Snake::GetBodyParts() const
{
	return bodyParts;
}

void Snake::SetHeadDirection(const Direction& direction)
{
	// Snake can't move to back of its direction. So we need to check
	// if user wants to go to this direction.
	if ((headDirection == Direction::Up && direction == Direction::Down) ||
		(headDirection == Direction::Right && direction == Direction::Left) ||
		(headDirection == Direction::Down && direction == Direction::Up) ||
		(headDirection == Direction::Left && direction == Direction::Right) ||
		direction == Direction::None)
		return;

	headDirection = direction;
	canChangeDirection = false;
}

void Snake::Kill()
{
	isAlive = false;
}

void Snake::ExpandTail()
{
	bodyParts.push_back(bodyParts[bodyParts.size() - 1]);
}

bool Snake::CanChangeDirection() const
{
	return canChangeDirection;
}

bool Snake::NeedToMove(double deltaTime)
{
	passedDistance += SPEED * deltaTime;

	if (passedDistance >= cellsNeededToPass)
	{
		cellsNeededToPass++;
		canChangeDirection = true;
		return true;
	}

	return false;
}