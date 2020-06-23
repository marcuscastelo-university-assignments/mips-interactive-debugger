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
    
    return vec;
}

string rtrim (string str) {
    int size = str.size();

    while (size > 0 and (str[size-1] == '\n' or str[size-1] == '\r' or str[size-1] == '\t' or str[size-1] == '\v' or str[size-1] == '\f' or str[size-1] == ' ')) {
        str.pop_back();
        size = str.size();
    }

    return str;
}

string ltrim (string str) {
    str.erase(0, str.find_first_not_of("\n\r\t\v\f "));
    
    return str;
}


string trim (string str) {
    return ltrim(rtrim(str));       
}


string replaceAllChars (string str, char toReplace, char substitute) {
    if (str.empty())
        return str;

    int pos;
    while ((size_t) (pos = str.find(toReplace)) != (string::npos)) {
        str[pos] = substitute;
    }

    return str;
}

void printLine (int size) {
    for (int i = 0; i < size; i++)
            printf("%c", '-');
        printf("\n");
}
