#ifndef __PROGRAM__H__
#define __PROGRAM__H__

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
        
        bool addInstruction(string inst);
        string getInstruction(int pos, bool withCommas=false);
        size_t getInstructionsVectorSize(void);
        
        void addLabelPos(string label, int pos);
        map<string, int>::iterator getLabelPos(string label);
        bool hasLabel(string label);
        void printLabel(string label="");

        void addBreakpoint(int pos);
        void removeBreakpoint(int pos);
        bool isBreakpoint(int pos);
        void printBreakpoints();

        void printInstructions(string label="", FILE *file_ptr=stdout);

};

bool isLabel(string str);
void printSingleInstruction(string line, FILE *file_ptr=stdout);
void printSingleLabel(string label, int addr);
void printSingleBreakpoint(int addr);

#endif