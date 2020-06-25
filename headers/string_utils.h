#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <vector>
#include <string>

using namespace std;

vector<string> split(const string& str, const string& delimiter=" ");
string trim(const string& str);
string replaceAllChars(const string& str, char toReplace, char substitute);
void printLine(int size);
string getLine(FILE *file_ptr=stdin);
string preventAbsolutePath(const string& str);

bool isInteger(const std::string & s);

#endif