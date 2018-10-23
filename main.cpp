/*
Console extecutable, makes use of the BullCowGame class
This acts as the view in a MVC pattern, and is responsibe for all user interaction. For logic see the BullCowGame Class

Trying C++ game
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
FText GetValidGuess();
void PrintGameSummary();
int32 UserSetHiddenWordLength();

FBullCowGame BCGame; // Instatiate a new game


// Entrypoint for the application
int main()
{
	bool bPlayAgain = false;

	PrintIntro();

	do {
		BCGame.UserSizeRequest = UserSetHiddenWordLength();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;

	return;
}

void PlayGame()
{
	BCGame.Reset();


	int32 MaxTries = BCGame.GetMaxTries();

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?" << std::endl << std::endl;

	// Guess the number of times until the until game is won and still tries remining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTries() <= BCGame.GetMaxTries())
	{
		FText Guess = GetValidGuess();

		// Submit Valid Guess
		FBullCowCount BCCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls: " << BCCount.Bulls;
		std::cout << " Cows: " << BCCount.Cows << "\n\n";
	}

	PrintGameSummary();

	return;
}

// Loop contiunily until a user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::INVALID;
	FText Guess = "";

	do {
		int32 CurrentTry = BCGame.GetCurrentTries();

		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ": Please guess the word: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "Please enter a isogram (No repeating letters)\n" << std::endl;
			break;
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word\n" << std::endl;
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "Please enter a word in all lowercase\n" << std::endl;
			break;
		default:
			// Assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // Loop until no errors

	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done!! You Win!! \n" << std::endl;
	}
	else
	{
		std::cout << "The Word was \"" << BCGame.GetHiddenWord() << "\"" << std::endl;
		std::cout << "Better Luck Next Time \n" << std::endl;
	}
}

// Ask the user for the word lenght they wish to guess
// Or ask for a random length word
int32 UserSetHiddenWordLength()
{
	bool IncorrectValue = true;
	int32 Number = 1;

	std::cout << "Please choose a word length (4-10)" << std::endl;
	std::cout << "Or enter 0 for random word" << std::endl;
	std::cout << "Word length: ";

	while (IncorrectValue) {

		// Check if input is a number or a Negative
		while (!(std::cin >> Number) || Number < 0)
		{
			std::cout << "\n";
			std::cout << "Invalid input! Not a Number" << std::endl;
			std::cout << "Please choose a word length (4-10)" << std::endl;
			std::cout << "Or enter 0 for random word" << std::endl;
			std::cout << "Word length: ";
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}

		// Check if Number is within select range
		if (Number == 0 || (Number > 3 && Number < 11))
		{
			IncorrectValue = false;
		}
		else {
			std::cout << "\n";
			std::cout << "Invalid Value!" << std::endl;
			std::cout << "Please choose a word length (4-10)" << std::endl;
			std::cout << "Or enter 0 for random word" << std::endl;
			std::cout << "Word length: ";

		}

		// Clear cin between asking for string or number
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	std::cout << "\n";
	return Number;
}


bool AskToPlayAgain()
{
	FText Response = "";
	bool ValidResponse = true;

	do
	{
		std::cout << "Do you want to play again (Y/N)? ";
		std::getline(std::cin, Response);

		if (tolower(Response[0]) == 'y')
		{
			std::cout << std::endl;
			return true;
		}
		else if (tolower(Response[0]) == 'n')
		{
			std::cout << std::endl;
			return false;
		}
		else
		{
			ValidResponse = false;
		}
	} while (!ValidResponse);
}
