#ifndef __PROGRAM__H__
#define __PROGRAM__H__

#include <vector>
#include <map>
#include <string>
class Program {
    private:
        std::vector <std::string> *instructions;
        std::map <std::string, int> *labelsAddresses;
        std::map <int, bool> *breakpointsAddresses;
    
    public:
        Program();
        Program(const Program& program);
        ~Program();
        
        bool addInstruction(std::string inst);
        std::string getInstruction(int pos, bool withCommas=false);
        size_t getInstructionsVectorSize(void);
        
        void addLabelPos(std::string label, int pos);
        std::map<std::string, int>::iterator getLabelPos(std::string label);
        bool hasLabel(std::string label);
        void printLabel(std::string label="");

        void addBreakpoint(int pos);
        void removeBreakpoint(int pos);
        bool isBreakpoint(int pos);
        void printBreakpoints();

        void printInstructions(std::string label="", FILE *file_ptr=stdout);

};

bool isLabel(std::string str);
void printSingleInstruction(std::string line, FILE *file_ptr=stdout);
void printSingleLabel(std::string label, int addr);
void printSingleBreakpoint(int addr);

#endif