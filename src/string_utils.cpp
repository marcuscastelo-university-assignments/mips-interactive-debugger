#include "string_utils.h"
#include <iostream>
#include <stdexcept>
#include <regex>

using namespace std;

vector<string> split(const string& str_orig, const string& delimiter) {
    string str = str_orig;
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

string rtrim (const string& str_orig) {
    string str = str_orig;
    int size = str.size();

    while (size > 0 and (str[size-1] == '\n' or str[size-1] == '\r' or str[size-1] == '\t' or str[size-1] == '\v' or str[size-1] == '\f' or str[size-1] == ' ')) {
        str.pop_back();
        size = str.size();
    }

    return str;
}

string ltrim (const string& str_orig) {
    string str = str_orig;
    str.erase(0, str.find_first_not_of("\n\r\t\v\f "));
    
    return str;
}


string trim (const string& str) {
    return ltrim(rtrim(str));       
}

vector<string> trimVec(vector<string> str_vec) {
    int size = str_vec.size();

    for (int i = 0; i < size; i++) {
        str_vec[i] = trim(str_vec[i]);
    }

    return str_vec;
}


string replaceAllChars (const string& str_orig, char toReplace, char substitute) {
    string str = str_orig;
    if (str.empty())
        return str;

    size_t pos = 0;
    while ((pos = str.find(toReplace)) != (string::npos)) {
        str[(int)pos] = substitute;
    }

    return str;
}

void printLine (int size) {
    for (int i = 0; i < size; i++)
            printf("%c", '-');
        printf("\n");
}

string getLine(FILE *file_ptr) {
    char *tmp;
    fscanf(file_ptr, "%m[^\r\n]%*c", &tmp);

    if (tmp == NULL) {
        fscanf(file_ptr, "%*c");

        return string("");
    }

    if (tmp[0] == '\n')
        return string("");

    string str = string(tmp);
    str = trim(str);
    return str;
}

string preventAbsolutePath(const string& str_orig) {
    string str = str_orig;
    if (str.empty())
        return str;

    auto pos = str.rfind("/");
    if (pos != string::npos) {
        str.erase(0, pos+1);
    }

    return str;
}

bool isInteger(const std::string& s) {
    return std::regex_match(s, std::regex("^\\s*([+-]?[0-9]+)\\s*$"));
}

string removeComments(string str) {
    int pos = str.find('#');

    if ((unsigned long) pos != string::npos) {
        str.erase(str.begin()+pos, str.end());
    }

    return str;
}

string removeAllChars (string str, char c) {
    for (auto it = str.begin(); it != str.end(); it++) {
        if (*it == c)
            str.erase(it);
    }

    return str;
}

pair<string, string> parseRegisterOffset(string str) {
    int pos = str.find('(');
    if (pos == (int) string::npos) return make_pair("not", "offset");
    str.erase(str.end()-1);
    int size = str.size();

    string offset;
    if (pos == 0)
        offset = string("0");
    else
        offset = str.substr(0, pos);

    string reg = str.substr(pos+1, size-pos);

    return make_pair(reg, offset);
}

