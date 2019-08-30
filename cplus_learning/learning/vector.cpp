#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> temp = {1,2,3,4,5};
    // temp.assign(4,'0');
    // for(auto i=temp.begin(); i!= temp.end();i++){
    //     cout << *i <<endl;
    // }
    
    vector<int> v1,v2;
    v1.push_back(10);v1.push_back(20);
    v2.push_back(100);v2.push_back(200);
    // for(int i=0; i < v1.size(); ++i){
    //     cout << v1.at(i)<<endl;
    //     cout << v2.at(i)<<endl;
    // }

    vector< vector<int> > v_2d;
    v_2d.push_back(v1);
    v_2d.push_back(v2);
    
    cout << v_2d[0][0] <<endl;
    cout << v_2d[0][1] <<endl;
    cout << v_2d[1][0] <<endl;
    cout << v_2d[1][1] <<endl;

    v1[0] = 1000;
    cout << v1[0]<<endl;

    cout << v_2d[0][0] <<endl;
    cout << v_2d[0][1] <<endl;
    cout << v_2d[1][0] <<endl;
    cout << v_2d[1][1] <<endl;

    return 0;
}
