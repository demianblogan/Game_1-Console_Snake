#pragma once
#include <vector>
#include <memory>
#include "../Tools/Vector2.h"
#include "../Game/GameEnumerations.h"

class Apple;
class Walls;

class Snake
{
public:
	Snake(const Vector2u& initialPosition, const Vector2u& worldBoundaries);

	bool IsAlive() const;
	bool IsTouching(const Apple& apple) const;
	bool IsTouching(const Walls& walls) const;
	bool IsTouchingItself() const;
	void Move(double deltaTime, bool isClassicMode);
	const std::vector<Vector2u>& GetBodyParts() const;
	void SetHeadDirection(const Direction& direction);
	void Kill();
	void ExpandTail();
	bool CanChangeDirection() const;

private:
	bool NeedToMove(double deltaTime);

	std::vector<Vector2u> bodyParts;
	bool isAlive = true;
	Direction headDirection = Direction::None;
	static constexpr int SPEED = 8; // cells per second
	double passedDistance = 0;
	int cellsNeededToPass = 1;
	bool canChangeDirection = true;
	const Vector2u WORLD_BOUNDARIES;
};