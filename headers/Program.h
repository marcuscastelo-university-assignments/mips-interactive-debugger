#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include <map>
#include <string>
using namespace std;

class Program {
    private:
        vector <string> *instructions;
        map <string, int> *labelsPosition;
        map <int, bool> *breakpointsPosition;
    
    public:
        Program();
        ~Program();
        
        void addInstruction(string inst);
        string getInstruction(int pos);
        
        void addLabelPos(string label, int pos);
        map<string, int>::iterator getLabelPos(string label);
        bool hasLabel(string label);

        void addBreakpoint(int pos);
        void removeBreakpoint(int pos);
        bool isBreakpoint(int pos);

        void printInstructions(string label="");

};

bool isLabel(string str);
void printSingleInstruction(string line);

#endif