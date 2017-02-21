/* The game logic*/

#pragma once
#include <string>


using FString = std::string;
using int32 = int;

// used to count
struct FBullCowCount{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
};


class FBullCowGame {
public:
	FBullCowGame(); // constructor

	void Reset();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool isGameWon() const;
	
	EGuessStatus CheckGuessValidity(FString) const;

	//counts bulls & cows, and increasing try # assuming valid guess
	FBullCowCount SubmitGuess(FString);


private:
	// see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon;

	bool IsIsogram(FString) const;
	bool isLowercase(FString) const;
};