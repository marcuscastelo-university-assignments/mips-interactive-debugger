#include "string_utils.h"
#include <iostream>

using namespace std;

vector<string> split(string str, const string delimiter) {
    size_t pos = 0;
    string token;
    vector<string> vec;

    if (str.empty())
        return vec;

    while ((pos = str.find(delimiter)) != string::npos) {
        token = str.substr(0, pos);
        if (token.empty() == false)
            vec.push_back(token);
        str.erase(0, pos + delimiter.length());
    }

    vec.push_back(str.substr(0, str.size()));
    cout << vec.size() << endl;
    
    return vec;
}