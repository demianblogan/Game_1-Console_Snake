#include "Walls.h"

#include "../Tools/FileManager.h"

bool Walls::InitializeFromFile(const std::string& filename)
{
	std::string content;

	if (!FileManager::ReadTextFromFile(filename, content))
		return false;

	// Every level in the game has walls. Wall is marked by '*' character.
	// So we need to go through the file's content, find '*' characters,
	// define their positions in this file, convert it to Vector2u, and put
	// it to wallPositions vector.

	size_t contentSize = content.size();
	int columnIndex = 0;
	int rowIndex = 0;

	for (size_t i = 0; i < contentSize; i++)
	{
		if (content[i] == '\n')
		{
			rowIndex++;
			columnIndex = -1;
		}
		else if (content[i] == '*')
		{
			Vector2u position = 
			{ 
				unsigned(columnIndex), 
				unsigned(rowIndex)
			};

			wallPositions.push_back(position);
		}

		columnIndex++;
	}

	return true;
}

const std::vector<Vector2u>& Walls::GetWallPositions() const
{
	return wallPositions;
}