#pragma once
#include <string>

class Score
{
public:
	void AddPoints(int points);
	int Value() const;
	void Reset();

	std::string ToString() const;

private:
	int value = 0;
};

bool operator==(const Score& score1, const Score& score2);
bool operator>(const Score& score1, const Score& score2);