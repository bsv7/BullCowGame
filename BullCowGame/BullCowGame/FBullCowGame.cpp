#include "FBullCowGame.h"
#include <map>

#define TMap std::map

FBullCowGame::FBullCowGame() {	Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }
bool FBullCowGame::isGameWon() const { return bIsGameWon; }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,7}, {5,10},{6,15} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
	//return MyMaxTries; 
}


void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "plane"; // It has to be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;

	bIsGameWon = false;
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) { // if the guess isn't an isogram
		return EGuessStatus::Not_Isogram;
	}
	else if (!isLowercase(Guess)){// if the guess isn't all lowecase, return error
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != MyHiddenWord.length()) {// if the guess length is wrong
		return EGuessStatus::Wrong_Length;
	}
	else {//return OK
		return EGuessStatus::OK;
	}
}

// recieved a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();

	// loop through all letters in the guess

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//if they match
			if (MyHiddenWord[MHWChar] == Guess[GChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bIsGameWon = true;
	}
	else {
		bIsGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) {
		return true;
	}
	//setup our map
	TMap <char, bool> LetterSeen;

	// loop through all the letters of the word
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
		
	}
		// if the letter is in the map
	//otherwise
		// add the letter to the map as seen
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::isLowercase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
