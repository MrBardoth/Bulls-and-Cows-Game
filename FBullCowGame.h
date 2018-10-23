/*
Houses the game logic for a simple guessing game. User has no interaction in this part of the code
*/

#pragma once
#include <string>
#include <fstream>
#include <map>
#include <time.h>


// Make syntax UE4 friendly
using FString = std::string;
using int32 = int;
#define TMap std::map
#define TMultiMap std::multimap

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	INVALID,
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH,
	NOT_LOWERCASE,
	NOT_A_WORD
};

class FBullCowGame
{
public:
	FBullCowGame(); // Constructor

	int32 UserSizeRequest = 15;

	int32 GetMaxTries() const;
	int32 GetCurrentTries() const;
	int32 GetHiddenWordLength() const;
	FString GetHiddenWord() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);
	FString SetIsogramHiddenWord(int32 size);


private:

	// See constructor for Initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bIsGameWon;
	TMultiMap<int32, FString> IsogramsMap;
	typedef TMultiMap <int32, std::string>::iterator MMapIT;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;

	void SetIsogramMap();
	void Trim(FString& string);
};
