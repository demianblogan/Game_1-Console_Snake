#include "Field.h"

#include <iostream>
#include "../Tools/Console.h"
#include "../Tools/Random.h"
#include "WorldHeaders.h"

Field::Field(const Vector2u& size)
	: size(size)
{
	AllocateField();
	Clear();
}

Field::~Field()
{
	DeallocateField();
}

void Field::Render() const
{
	Console::ResetCursorPosition();

	unsigned rows = size.y, columns = size.x;
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < columns; j++)
			std::cout << field[i][j];
		std::cout << '\n';
	}
}

unsigned Field::GetRows() const
{
	return size.y;
}

unsigned Field::GetColumns() const
{
	return size.x;
}

void Field::Set(const Walls& walls)
{
	const std::vector<Vector2u>& wallPositions = walls.GetWallPositions();

	size_t wallSize = wallPositions.size();
	for (unsigned i = 0; i < wallSize; i++)
		field[wallPositions[i].y][wallPositions[i].x] = char(WorldElement::Wall);
}

void Field::Set(const Apple& apple)
{
	const Vector2u& applePosition = apple.GetPosition();
	field[applePosition.y][applePosition.x] = char(WorldElement::Apple);
}

void Field::Set(const Snake& snake)
{
	const std::vector<Vector2u>& snakeBodyParts = snake.GetBodyParts();
	size_t snakeBodyPartsSize = snakeBodyParts.size();

	if (snakeBodyPartsSize == 0)
		return;

	// Set head:
	const Vector2u& headPosition = snakeBodyParts[0];
	field[headPosition.y][headPosition.x] = char(WorldElement::SnakeHead);

	// Set other parts:
	for (size_t i = 1; i < snakeBodyPartsSize; i++)
	{
		const Vector2u& partPosition = snakeBodyParts[i];
		field[partPosition.y][partPosition.x] = char(WorldElement::SnakePart);
	}
}

void Field::Clear()
{
	unsigned rows = size.y, columns = size.x;
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < columns; j++)
			field[i][j] = char(WorldElement::Empty);
}

Vector2<unsigned> Field::GetRandomEmptyPoint() const
{
	Vector2u randomPosition;
	unsigned rows = size.y, columns = size.x;

	do
	{
		// 0 and (columns - 1)/(rows - 1) are walls.
		// So the range of search is between this range.
		randomPosition.x = Random::GenerateInt(1, columns - 1);
		randomPosition.y = Random::GenerateInt(1, rows - 1);

	} while (field[randomPosition.y][randomPosition.x] != char(WorldElement::Empty));

	return randomPosition;
}

void Field::AllocateField()
{
	unsigned rows = size.y, columns = size.x;

	field.resize(rows);
	
	for (unsigned i = 0; i < rows; i++)
		field[i].resize(columns);
}

void Field::DeallocateField()
{
	field.clear();
}