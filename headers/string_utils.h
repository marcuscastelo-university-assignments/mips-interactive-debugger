#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <vector>
#include <string>

using namespace std;

vector<string> split(string str, const string delimiter=" ");
string trim(string str);
string replaceAllChars(string str, char toReplace, char substitute);
void printLine(int size);


#endif