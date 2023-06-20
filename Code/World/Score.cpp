#include "Score.h"

void Score::AddPoints(int points)
{
	if (points > 0)
		value += points;
}

int Score::Value() const
{
    return value;
}

void Score::Reset()
{
	value = 0;
}

std::string Score::ToString() const
{
	std::string scoreStr;

	if (value < 10) // only 1 digit
		scoreStr = "00" + std::to_string(value);
	else if (value < 100) // only 2 digits
		scoreStr = "0" + std::to_string(value);
	else
		scoreStr = std::to_string(value);

	return scoreStr;
}

bool operator==(const Score& score1, const Score& score2)
{
	return score1.Value() == score2.Value();
}

bool operator>(const Score& score1, const Score& score2)
{
	return score1.Value() > score2.Value();
}