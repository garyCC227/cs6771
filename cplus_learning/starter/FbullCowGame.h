#ifndef __FBULLCOWGAME__
#define __FBULLCOWGAME__

#include <string>


using int32 = int;
using FString = std::string;


struct BullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FbullCowGame
{
private:
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
    bool isGameWon;

    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
public:
    FbullCowGame();

    void Reset();
    int32 GetMaxTries() const;
    int32 GetCurrentTry();
    bool IsGameWon();
    EGuessStatus CheckGuessValidity(FString) const;
    int32 getHiddenWordLength() const;
    // provide a method for couting bulls and cows and increasing try
    BullCowCount SubmitGuess(FString);
    

};

#endif