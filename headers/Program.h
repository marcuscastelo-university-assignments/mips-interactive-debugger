#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include <map>
#include <string>
using namespace std;

class Program {
    private:
        vector <string> *instructions;
        map <string, int> *labelsAddresses;
        map <int, bool> *breakpointsAddresses;
    
    public:
        Program();
        ~Program();
        
        void addInstruction(string inst);
        string getInstruction(int pos);
        
        void addLabelPos(string label, int pos);
        map<string, int>::iterator getLabelPos(string label);
        bool hasLabel(string label);
        void printLabel(string label="");

        void addBreakpoint(int pos);
        void removeBreakpoint(int pos);
        bool isBreakpoint(int pos);

        void printInstructions(string label="", FILE *file_ptr=stdout);

};

bool isLabel(string str);
void printSingleInstruction(string line, FILE *file_ptr=stdout);
void printSingleLabel(string label, int pos);

#endif