#include "common.h"
#include <iostream>

void printStrings(vector<string> v){
    cout<<"========================================" << endl;
    for(auto& s: v){
        cout<< s << endl;
    }
    cout<<"========================================" << endl;
}

void printArray(vector<vector<int>> v){
    cout<<"****************************************" << endl;
    for(auto& s: v){
        cout << "[";
        for(int i=0; i<s.size(); i++){
            if(i != 0){
                cout<< ",";
            }
            cout << s[i];
        }
        cout<< "]" << endl;
    }
    cout<<"****************************************" << endl;
}