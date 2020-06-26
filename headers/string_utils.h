#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <vector>
#include <string>
#include <utility>

using namespace std;

std::vector<std::string> split(const std::string& str, const std::string& delimiter=" ");
std::string trim(const std::string& str);
std::vector<std::string> trimVec(std::vector<std::string> str);
std::string replaceAllChars(const std::string& str, char toReplace, char substitute);
std::string removeAllChars(std::string str, char c);
void printLine(int size);
std::string getLine(FILE *file_ptr=stdin);
std::string preventAbsolutePath(const std::string& str);
std::string removeComments(std::string str_vec);
std::pair<std::string, std::string> parseRegisterOffset(std::string str);
bool isInteger(const std::string & s);

#endif