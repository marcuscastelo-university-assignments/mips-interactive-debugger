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
        std::string getInstruction(int pos, bool withCommas=false) const;
        size_t getInstructionsVectorSize(void) const;
        
        void addLabelPos(std::string label, int pos);
        std::map<std::string, int>::iterator getLabelPos(const std::string& label) const;
        bool hasLabel(std::string label) const;
        void printLabel(std::string label="") const;

        void addBreakpoint(int pos);
        void removeBreakpoint(int pos);
        bool isBreakpoint(int pos) const;
        void printBreakpoints() const;

        void printInstructions(std::string label="", FILE *file_ptr=stdout) const;

};

bool isLabel(std::string str);
void printSingleInstruction(std::string line, FILE *file_ptr=stdout);
void printSingleLabel(std::string label, int addr);
void printSingleBreakpoint(int addr);

#endif