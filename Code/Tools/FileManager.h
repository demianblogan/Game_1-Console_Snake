#pragma once
#include <string>

enum class ColorTheme;
class Score;
struct Level;

// class FileManager is a static class that provides methods of reading from and writing into a file
// different kind of game information, such as ColorTheme, Score and Level.
class FileManager
{
public:
	static bool ReadTextFromFile(const std::string& filename, std::string& content);
	static bool ReadColorThemeFromFile(const std::string& filename, ColorTheme& theme);
	static bool ReadScoreTableFromFile(const std::string& filename, Score scoreTable[], size_t size);
	static bool ReadCompanyProgress(const std::string& filename, Level levels[], size_t size);

	static bool WriteTextInFile(const std::string& filename, const std::string& content);
	static bool WriteColorThemeInFile(const std::string& filename, const ColorTheme& theme);
	static bool WriteCompanyProgressInFile(const std::string& filename, const Level levels[], size_t size);
	static bool WriteScoreTableInFile(const std::string& filename, const Score scoreTable[], size_t size);
};