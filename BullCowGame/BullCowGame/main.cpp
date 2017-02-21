/* This is the console executable, that make use of the BullCow class
   This acts as the view in a MVC pattern, and is responsible for all
   user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes
void PrintIntro();
void PlayGame();
FText ValidGetGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

// entry point
int main() {

	bool bToPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bToPlayAgain = AskToPlayAgain();

	} while (bToPlayAgain);
	return 0;
}

// plays to a single player
void PlayGame()
{
	BCGame.Reset();
	int32 Max = BCGame.GetMaxTries();

	// loop asking for guess words while the game 
	// is NOT won and it does not reach the maximun number of tries
	while (!BCGame.isGameWon() && BCGame.GetCurrentTry() <= Max) {

		FText Guess = ValidGetGuess();

		// Submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();

}

void PrintIntro() {

	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         n_n " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength()<< " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

FText ValidGetGuess() {
	FText Guess;
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		int32 TryNumber = BCGame.GetCurrentTry();
		//get a guess from the player
		std::cout << "Try " << TryNumber << " of "<< BCGame.GetMaxTries()<<". Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n)";
	FText Response;
	getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.isGameWon()) {
		std::cout << "YOU WON\n";
	}
	else {
		std::cout << "YOU LOST :(\n";
	}
}

