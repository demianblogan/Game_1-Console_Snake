#pragma once
#include <vector>
#include <string>
#include "../Tools/Vector2.h"

class Walls
{
public:
	bool InitializeFromFile(const std::string& filename);
	const std::vector<Vector2u>& GetWallPositions() const;

private:
	std::vector<Vector2u> wallPositions;
};