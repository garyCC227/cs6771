#include <iostream>

using namespace std;

#define MAX_LEVEL 11

int is_correct(int sum, int product, int guestSum, int guestProduct, int difficulty);
int playGame(int difficulty);

int main(int argc, char const *argv[])
{
    int levelDifficulty = 1;
    while(levelDifficulty < MAX_LEVEL){
        
        if(playGame(levelDifficulty)){
            ++levelDifficulty;
        }
        cin.clear();
        cin.ignore();
        
    }

    return 0;
}

int  playGame(int difficulty){
    cout << "You are a secret agent breaking into a level " << difficulty;
    cout << endl;
    cout << "Enter the correct code to continue..." << endl;

    int a,b,c;
    a = rand()%difficulty+1;
    b = rand()%difficulty+1;
    c = rand()%difficulty+1;

    int sum = a + b + c;
    int product = a*b*c;

    cout << "They are three number in the code" <<endl;
    cout << "The codes add-up to: " << sum << endl;
    cout << "The codes multiply to give: " <<product << endl;

    int guestA, guestB, guestC;
    cin >> guestA >> guestB >> guestC;

    int guestSum = (guestA + guestB + guestC);
    int guestProduct = (guestA * guestB * guestC);

    cout << "You entered: " << guestA << guestB << guestC << endl;
    // cout << "Add-up to: " << (guestA + guestB + guestC) << endl;
    // cout << "mutiply to give: " << (guestA * guestB * guestC) << endl;
    
    return is_correct(sum, product, guestSum, guestProduct, difficulty);
}

int is_correct(int sum, int product, int guestSum, int guestProduct, int difficulty){
    if(guestSum == sum && guestProduct == product){
        cout << "*** You win this level "<< difficulty << " ***\n\n\n";
        return 1;
    }else{
        cout << "** You entered the wrong code, try again!! **\n\n\n" << endl;
    }
    return 0;
}