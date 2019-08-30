#include <iostream>
#include <string>
#include <map>

using namespace std;


int main(int argc, char const *argv[])
{
    // string temp = "hello";
    // string s2 (temp, 3); // lo
    // string s3 (temp,0,3); // hel
    // string s4(temp);    //hello
    // cout << s2 << endl;
    // cout << s3 << endl;
    // cout << s4 << endl;
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string value = "XZNLWEBGJHQDYCTKFUOMPCIASRxznlwbgjhqdyvtkfuompciasr";
    map<char, char> encrypt;
    map<char, char> decode;
    for(auto i = 0; i < alphabet.size(); i++){
        auto e_pair = make_pair(alphabet[i],value[i]);
        auto d_pair = make_pair(value[i],alphabet[i]);
        encrypt.insert(e_pair);
        decode.insert(d_pair);
    }

    string temp;
    cout << "Enter your string: \n";
    getline(cin, temp);
    string output;
    for(auto e: temp){
        output += encrypt[e];
    }
    cout << "output is: " << output << endl;
    return 0;
}
