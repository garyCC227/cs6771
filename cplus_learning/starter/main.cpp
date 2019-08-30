#include <iostream>
#include <string>
#include "FbullCowGame.h"
#include <map>


void playGame(FString* Guess);
void GameIntro();
bool AskToPlayAgain();
bool GetValidGuess(FString* Guess);
void printGameSummary();

FbullCowGame BCGame;
    
int main(int argc, char const *argv[])
{
    // FString Guess;
    // bool bPlayAgain = false;
    // do{
    //     GameIntro();
    //     playGame(&Guess);
    //     bPlayAgain = AskToPlayAgain();
        
    // }while(bPlayAgain);

    // printGameSummary();
    std::map<FString, int> temp;
    temp["hello"] = 1;
    std::cout << temp["hello"];

    return 0;
}

bool AskToPlayAgain(){
    std::cout << "*** Do you want to play again with the same hidden word? ***\n";
    FString res = "";
    getline(std::cin, res);
    std::cout<<"\n\n\n\n";
    return (res[0] == 'y' || res[0] == 'Y');

}
void GameIntro(){
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << "Can you guess " << BCGame.getHiddenWordLength() << " letter isogram I'am thinking of?\n";
    std::cout << "Enter you guess: \n";
}

bool GetValidGuess(FString* Guess){
    //get guess
    getline(std::cin, *Guess);

    EGuessStatus status = BCGame.CheckGuessValidity(*Guess);
    switch (status)
    {
    case EGuessStatus::Wrong_Length:
        std::cout << "Please enter a " << BCGame.getHiddenWordLength() << " letters word. \n\n";
        return false;
    case EGuessStatus::OK:
        return true;
    case EGuessStatus::Not_Lowercase:
        std::cout << "Please enter a lower case letter word!\n\n";
        return false;
    case EGuessStatus::Not_Isogram:
        std::cout << "Not a Isogram word.\n\n";
        return false;
    default:
        break;
    }

    return true;
}

void playGame(FString* Guess){
    BCGame.Reset();

    int32 MaxTries = BCGame.GetMaxTries();
    std::cout << "Maximum tries is: " << MaxTries << "\n\n";

    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
        int32 CurrTries = BCGame.GetCurrentTry();
        std::cout << "Current tries is: " << CurrTries << "\n";

        while(true){
            if(GetValidGuess(Guess)){ break; }
        };

        BullCowCount BullCowCount = BCGame.SubmitGuess(*Guess);
        std::cout << "Bull count: " << BullCowCount.Bulls <<", " ;
        std::cout << "Cow count: " << BullCowCount.Cows <<"\n\n\n";
    }
    
}

void printGameSummary(){
    if(BCGame.IsGameWon()){
        std::cout << "WELL DOEN - YOUR WIN!\n";
    }else{
        std::cout << "Better luck next time!\n";
    }
}