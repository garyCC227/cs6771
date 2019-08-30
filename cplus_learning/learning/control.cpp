#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using FString = std::string;

void menu_intro();
void show(std::vector<int> list);
int mean(std::vector <int> list);

int main(int argc, char const *argv[])
{
    std::vector<int> HiddenList = {1,2,3,4,5,6,7};
    std::vector<int> const emptyList = {};
    std::vector<int> list = HiddenList;

    bool run = true;
    FString tempUse;
    do
    {
        menu_intro();
        //getting menu option
        FString input;
        getline(std::cin,input);
        
        
        //options
        switch (tolower(input[0]))
        {
        case 'p':
            if (list.size() == 0){
                std::cout << "[] - the list is empty.\n";
            }else{
                show(list);
            }
            break;
        case 'a':
            do{
                std::cout << "Enter the adding number:  ";
                getline(std::cin, tempUse);
                int temp;
                try {
                    
                    temp = std::stoi(tempUse);
                }
                catch(std::exception){
                    std::cout << "Enter again please \n\n";
                    continue;
                }
                list.push_back(temp);
                break;
            }while(true);
            show(list);
            break;
        case 'm':
            if(list.size() == 0){
                std::cout << "Unable to calculate the mean - no data \n";
            }else{
                std::cout << "Mean is: " << mean(list) << std::endl;
            }
            break;
        case 's':
            if(list.size() == 0){
                std::cout << "no data\n";
            }else{
                std::vector<int>::iterator sm = std::min_element(std::begin(list), std::end(list));
                std::cout << "smallest element is " << *sm << std::endl;
            }
            break;
        case 'l':
            if(list.size() == 0){
                std::cout << "no data\n";
            }else{
                std::vector<int>::iterator max = std::max_element(std::begin(list), std::end(list));
                std::cout << "smallest element is " << *max << std::endl;
            }
            break;
        case 'q':
            run = false;
            break;

        default:
            std::cout << "Unknown option. please try again\n";
            break;
        }
    } while (run);
    


    return 0;
}

void menu_intro(){
    std::cout << "\n\n\n\nthere is a list of options you can select.\n ";
    std::cout << "P - Print numbers\n";
    std::cout << "A - Add a numbers\n";
    std::cout << "M - Display mean of the numbers\n";
    std::cout << "S - Display the smallest numbers\n";
    std::cout << "L - Display the largest  numbers\n";
    std::cout << "Q - Quit\n\n";
}

void show(std::vector <int> list){
    std::cout << "[ ";
    for(auto element : list){
        std::cout << element <<" ";
    }
    std::cout << "]\n";
}

int mean(std::vector <int> list){
    int sum, cout = 0;
    for(cout; cout < list.size(); cout++){ sum+=list[cout]; }

    return sum / cout;
}

