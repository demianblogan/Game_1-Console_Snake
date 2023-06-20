#include "FileManager.h"

#include <fstream>
#include "../Game/GameEnumerations.h"
#include "../World/Score.h"
#include "../World/Level.h"

bool FileManager::ReadTextFromFile(const std::string& filename, std::string& content)
{
	// Open file:
	std::ifstream fileStream(filename);
	if (!fileStream.is_open())
		return false;

	// Delete previous content:
	content.clear();

	// Read new content from file:
	std::string textLine;

	while (!fileStream.eof())
	{
		std::getline(fileStream, textLine);
		textLine.push_back('\n'); // std::getline doesn't add '\n' char
		content += textLine;
	}

	return true;
}

bool FileManager::ReadColorThemeFromFile(const std::string& filename, ColorTheme& theme)
{
	// Open file (in binary mode):
	std::ifstream fileStream(filename, std::ios::binary);

	// There can be no files or the file might be inaccessible. In this case we choose
	// default theme.
	if (!fileStream.is_open())
	{
		theme = ColorTheme::Black_Green;
		return true;
	}

	// Read theme. File can be empty. In this case it's incorrect.
	if (!fileStream.read(reinterpret_cast<char*>(&theme), sizeof(theme)))
		return false;

	if (int(theme) < int(ColorTheme::Black_Green) || int(theme) > int(ColorTheme::LightYellow_Purple))
		return false;

	return true;
}

bool FileManager::ReadScoreTableFromFile(const std::string& filename, Score scoreTable[], size_t size)
{
	// Open file (in binary mode):
	std::ifstream fileStream(filename, std::ios::binary);

	// There might be no files or the file might be inaccessible. In this case score table is already
	// set by hardcoded values.
	if (!fileStream.is_open())
		return true;

	for (size_t i = 0; i < size; i++)
	{
		int score;

		// File might have more or less, than 'size' numbers.
		if (!fileStream.read(reinterpret_cast<char*>(&score), sizeof(int)))
			return false;

		scoreTable[i].AddPoints(score);
	}

	return true;
}

bool FileManager::ReadCompanyProgress(const std::string& filename, Level levels[], size_t size)
{
	std::ifstream fileStream(filename, std::ios::binary);

	// That's okay if company progress file doesn't exist. Levels will be hardcoded.
	if (!fileStream.is_open())
		return true;

	for (size_t i = 0; i < size; i++)
	{
		// If file contains not 'size' values - that's bad.
		if (!fileStream.read(reinterpret_cast<char*>(&levels[i].isOpen), sizeof(bool)))
			return false;
	}

	return true;
}

bool FileManager::WriteTextInFile(const std::string& filename, const std::string& content)
{
	// Open file:
	std::ofstream fileStream(filename);
	if (!fileStream.is_open())
		return false;

	// Write content in file:
	fileStream << content;

	return true;
}

bool FileManager::WriteColorThemeInFile(const std::string& filename, const ColorTheme& theme)
{
	// Open file:
	std::ofstream fileStream(filename, std::ios::binary);
	if (!fileStream.is_open())
		return false;

	// Write content in file:
	fileStream.write(reinterpret_cast<const char*>(&theme), sizeof(theme));

	return true;
}

bool FileManager::WriteCompanyProgressInFile(const std::string& filename, const Level levels[], size_t size)
{
	// Open file:
	std::ofstream fileStream(filename, std::ios::binary);
	if (!fileStream.is_open())
		return false;

	for (size_t i = 0; i < size; i++)
		fileStream.write(reinterpret_cast<const char*>(&levels[i].isOpen), sizeof(bool));

	return true;
}

bool FileManager::WriteScoreTableInFile(const std::string& filename, const Score scoreTable[], size_t size)
{
	// Open file:
	std::ofstream fileStream(filename, std::ios::binary);
	if (!fileStream.is_open())
		return false;

	for (size_t i = 0; i < size; i++)
	{
		int score = scoreTable[i].Value();
		fileStream.write(reinterpret_cast<const char*>(&score), sizeof(int));
	}

	return true;
}