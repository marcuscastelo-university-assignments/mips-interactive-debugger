#ifndef __PROGRAM__H__
#define __PROGRAM__H__

#include <vector>
#include <map>
#include <string>
class Program {
    private:
        std::map <int, std::string> *instructions;
        std::map <std::string, int> *labelsAddresses;
        std::map <int, bool> *breakpointsAddresses;
    
    public:
        Program();
        Program(const Program& program);
        ~Program();
        
        void clear();

        bool addInstruction(std::string inst);
        std::string getInstruction(int pos, bool withCommas=false) const;
        size_t getInstructionsMapSize(void) const;
        
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
void printSingleInstruction(std::string line, int pos, FILE *file_ptr=stdout);
void printSingleLabel(std::string label, int addr);
void printSingleBreakpoint(int addr);

#endif