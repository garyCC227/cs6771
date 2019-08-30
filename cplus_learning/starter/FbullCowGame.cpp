#include "FbullCowGame.h"
#include <map>

#define TMap std::map 


int32 FbullCowGame::GetMaxTries() const{
    TMap <int,int> Tryies = {
        {1,2},
        {2,3},
        {3,4},
        {4,5},
        {5,6},
        {6,16}
    };
    return Tryies[MyHiddenWord.length()];
}

int32 FbullCowGame :: GetCurrentTry(){
    return MyCurrentTry;
}

void FbullCowGame::Reset(){
    MyCurrentTry = 1;
    constexpr int32 temp = 5;
    MyMaxTries = temp;

    const FString HIDDEN_WORD = "plane";
    MyHiddenWord = HIDDEN_WORD;

    isGameWon = false;
}

bool FbullCowGame::IsGameWon(){
    return isGameWon;
}

//check the error type
EGuessStatus FbullCowGame::CheckGuessValidity(FString Guess) const{
    if(!IsLowercase(Guess)){
        return EGuessStatus::Not_Lowercase;
    }
    else if(!IsIsogram(Guess)){
        return EGuessStatus::Not_Isogram;
    }
    else if(Guess.length() != getHiddenWordLength()){
        return EGuessStatus::Wrong_Length;
    }
    
    return EGuessStatus::OK;
}

FbullCowGame::FbullCowGame(){
    Reset();
}

int32 FbullCowGame::getHiddenWordLength() const{
    return MyHiddenWord.length();
}

//recieve a VALID guess, increament try
BullCowCount FbullCowGame::SubmitGuess(FString Guess){
    MyCurrentTry +=1;

    BullCowCount BullCowCount;
    int32 HiddenWordLength = MyHiddenWord.length();

    //lopp through all letters in the guess
    for(int32 MHWChar=0; MHWChar < HiddenWordLength; MHWChar++){
        //compare with the hidden word
        for(int32 Gchar=0; Gchar < HiddenWordLength; Gchar++){
            //if they match
            if(Guess[Gchar] == MyHiddenWord[MHWChar]){
                //if they are in the same place, bull++
                if(MHWChar == Gchar){
                    BullCowCount.Bulls++;
                }else{
                    BullCowCount.Cows++;
                }
            }
        }
    }
    if(BullCowCount.Bulls == HiddenWordLength){
        isGameWon = true;
    }else{
        isGameWon = false;
    }

    return BullCowCount;
}


bool FbullCowGame::IsIsogram(FString Guess) const{
    // treat 0 and 1 letter words as isograms
	if (Guess.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
    for (auto letter: Guess){
        letter = tolower(letter);
        if(LetterSeen[letter]){
            return false;
        }else{
            LetterSeen[letter] = true;
        }
    }

	return true; // for example in cases where /0 is entered
}

bool FbullCowGame::IsLowercase(FString Guess)const{
    for(auto letter : Guess){
        if(!islower(letter)){
            return false;
        }
    }
    return true;
}