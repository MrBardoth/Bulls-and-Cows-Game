#include "FBullCowGame.h"
#include <iostream>

// Default Constructor
FBullCowGame::FBullCowGame()
{
	SetIsogramMap();
	Reset();
}

int32 FBullCowGame::GetCurrentTries() const
{
	return MyCurrentTry;
}

bool FBullCowGame::IsGameWon() const
{
	return bIsGameWon;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

FString FBullCowGame::GetHiddenWord() const
{
	return MyHiddenWord;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {4,10}, {5,12}, {6,16}, {7,20}, {8,25}, {9,30},
				{10,35}, {11,40}, {12,45}, {13,50}, {14,55}, {15,60} };

	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = SetIsogramHiddenWord(UserSizeRequest);
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::NOT_ISOGRAM;
	}

	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::NOT_LOWERCASE;
	}

	// wrong length
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::WRONG_LENGTH;
	}

	// otherwise return ok
	else
	{
		return EGuessStatus::OK;
	}
}

// Recieves a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	//Loop through all letters in HiddenWord
		//For each letter compare against Guess
		// If they match, increment bulls if they're in the same place
		// increment cows if not
	for (int32 Count = 0; Count < MyHiddenWord.length(); Count++)
	{
		if (Guess[Count] == MyHiddenWord[Count])
		{
			BullCowCount.Bulls++;
		}
		else
		{
			for (int32 InnerCount = 0; InnerCount < MyHiddenWord.length(); InnerCount++)
			{
				if (Guess[Count] == MyHiddenWord[InnerCount])
				{
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == MyHiddenWord.length())
	{
		bIsGameWon = true;
	}
	else
	{
		bIsGameWon = false;
	}

	return BullCowCount;
}

// Selects a word of a length the user requests
FString FBullCowGame::SetIsogramHiddenWord(int32 size)
{
	srand(time(NULL));
	FString Guess;

	// Get random length if 0 is chosen
	if (size == 0) {
		size = std::rand() % (15 + 1 - 4) + 4;
	}

	// Get the values for Map key based on size
	std::pair<MMapIT, MMapIT>Iterators = IsogramsMap.equal_range(size);

	// Range is between the first value of the selected key (inclusive)
	// and the first value of the next key (Not inclusive)
	std::size_t Range = std::distance(Iterators.first, Iterators.second);

	// Get a random word between the range
	std::size_t Index = std::rand() % Range;

	// Move the iterator to that value
	std::advance(Iterators.first, Index);

	// Return word
	Guess = ((*Iterators.first).second);

	return Guess;
}

// Gets all the isograms out of the CSV file and puts it in a multimap 
// Size is the key for the key, value pairs
void FBullCowGame::SetIsogramMap()
{
	std::ifstream IsoFile("isograms.csv");
	FString Word;

	while (std::getline(IsoFile, Word, ','))
	{
		Trim(Word); // Remove leading and trailing whitespace
		IsogramsMap.insert(std::pair<int32, FString>(Word.length(), Word));
	}

	IsoFile.close();
	return;
}

// Remove the leading and trailing whitespace from a word
void FBullCowGame::Trim(FString & string)
{
	size_t Space = string.find_first_not_of(" \t");
	string.erase(0, Space);

	Space = string.find_last_not_of(" \t");
	if (FString::npos != Space)
	{
		string.erase(Space + 1);
	}

	return;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> LetterSeen;

	for (auto Letter : Guess)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowerCase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
