#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

void sort3(int& a, int& b, int& c);



int main() {
    cout << "Enter 3 numbers: \n";
    int a,b,c;
    cin >> a >> b >>c;

    sort3(a,b,c);

    return 0;
}

void sort3(int& a, int& b, int& c) {
    vector<int> list {a,b,c};
    sort(list.begin(), list.end());
    for(auto e: list){
        cout << e << " ";
    }
    cout << "\n";
};
