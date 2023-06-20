#include "GameException.h"

GameException::GameException(const std::string& errorMessage, const std::string& functionName, int lineNumber)
	: errorMessage(errorMessage), functionName(functionName), lineNumber(lineNumber)
{ }

const std::string& GameException::GetErrorMessage() const
{
	return errorMessage;
}

const std::string& GameException::GetFunctionName() const
{
	return functionName;
}

int GameException::GetLineNumber() const
{
	return lineNumber;
}

const char* GameException::what() const noexcept
{
	return errorMessage.c_str();
}
