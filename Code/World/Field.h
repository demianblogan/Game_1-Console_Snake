#pragma once
#include <memory>
#include <vector>
#include "../Tools/Vector2.h"

class Walls;
class Apple;
class Snake;

class Field
{
public:
	Field(const Vector2u& size);
	~Field();

	void Render() const;
	unsigned GetRows() const;
	unsigned GetColumns() const;

	void Set(const Walls& walls);
	void Set(const Apple& apple);
	void Set(const Snake& snake);

	void Clear();

	Vector2u GetRandomEmptyPoint() const;

private:
	enum class WorldElement : char
	{
		SnakeHead = 'O',
		SnakePart = 'o',
		Empty = ' ',
		Apple = 'A',
		Wall = '*'
	};

	void AllocateField();
	void DeallocateField();

	std::vector<std::vector<char>> field;
	Vector2u size; // rows & columns
};