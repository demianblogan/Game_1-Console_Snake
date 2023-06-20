#pragma once
#include <string>
#include <exception>

// class GameException is just a usuful container of information about possible game errors.
class GameException : public std::exception
{
public:
	GameException(const std::string& errorMessage = "Error", const std::string& functionName = "", int lineNumber = 0);

	const std::string& GetErrorMessage() const;
	const std::string& GetFunctionName() const;
	int GetLineNumber() const;

	virtual const char* what() const noexcept override;

private:
	std::string errorMessage;
	std::string functionName;
	int lineNumber;
};