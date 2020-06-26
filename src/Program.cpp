#include "Program.h"
#include "string_utils.h"
#include <stdexcept>

Program::Program() {
    instructions = new vector<string>();
    labelsAddresses = new map<string, int>();
    breakpointsAddresses = new map<int, bool>();
}

Program::~Program() {
    delete instructions;
    delete labelsAddresses;
    delete breakpointsAddresses;
}


/////INSTRUCTION/////
bool Program::addInstruction(string inst) {
    if (inst.empty())
        return false;

    if (isLabel(inst) and hasLabel(inst)) {
            printf("Can't have two labels with the same identifier\n");
            return false;
    }

    //TODO: parse register name
    if (isLabel(inst)) {
        vector<string> commandParts = split(inst);
        if (commandParts.size() >= 2) {
            printf("Can't have spaces in label's identifier. Ignoring this line: %s\n", inst.c_str());
            return false;
        }
        instructions->push_back(inst);
        addLabelPos(inst, getInstructionsVectorSize()-1);
    }
    else
        instructions->push_back(inst);
    
    return true;
}

string Program::getInstruction(int pos) {
    if (pos < 0 or pos >= (int) getInstructionsVectorSize())
        throw std::out_of_range("Position not allowed");

    return (*instructions)[pos];
}

size_t Program::getInstructionsVectorSize(void) {
    return instructions->size();
}   

void Program::printInstructions(string label, FILE *file_ptr) {
    int size = (int) getInstructionsVectorSize();
    
    if (label.empty()) {
        for (int i = 0; i < size; i++)
            printSingleInstruction(getInstruction(i), file_ptr);
        return;
    }

    auto it = getLabelPos(label);
    if (it == labelsAddresses->end()) {
        printf("Label %s undefined\n", label.c_str());
        return;
    }

    printSingleInstruction(getInstruction(it->second), file_ptr);
    for (int i = it->second+1; i < size; i++) {
        string inst = getInstruction(i);
        if (isLabel(inst))
            break;
        
        printSingleInstruction(inst, file_ptr);
    }  

    return;
}


/////LABEL/////
void Program::addLabelPos(string label, int pos) {
    if (label.empty())
        return;

    if (pos < 0 or pos >= (int) getInstructionsVectorSize())
        throw std::out_of_range("Position not allowed");
    
    if (isLabel(label) == false)
        return;

    label.pop_back();

    (*labelsAddresses)[label] = pos;

    return;
}

map<string,int>::iterator Program::getLabelPos(string label) {
    if (label.empty())
        return labelsAddresses->end();

    return labelsAddresses->find(label);
}

bool Program::hasLabel(string label) {
    if (label.empty())
        return false;

    if (label[label.size()-1] == ':')
        label.pop_back();

    return !(getLabelPos(label) == labelsAddresses->end());
}

void Program::printLabel(string label) {
    if (label.empty() == false) {
        if (hasLabel(label)) {
            printLine(25);    
            printSingleLabel(label, getLabelPos(label)->second);
            printLine(25);
        }

        return;
    }

    bool hasLabel = false;

    for (auto it = labelsAddresses->begin(); it != labelsAddresses->end(); it++) {
        printLine(25);
        printSingleLabel(it->first, it->second);
        hasLabel = true;
    }
    
    if (hasLabel)
        printLine(25);
    else
        printf("No labels to show\n");        
    
    return;
}


/////BREAKPOINTS/////
void Program::addBreakpoint(int pos) {
    if (pos < 0 or pos >= (int) getInstructionsVectorSize())
        throw std::out_of_range("Position not allowed");

    (*breakpointsAddresses)[pos] = true;

    return;
}

void Program::removeBreakpoint(int pos) {
    breakpointsAddresses->erase(pos);

    return;
}

bool Program::isBreakpoint(int pos) {
    return (*breakpointsAddresses)[pos];
}

void Program::printBreakpoints(void) {
    auto it = breakpointsAddresses->begin();
    
    if (breakpointsAddresses->end() == it) {
        printf("No breakpoints added\n");
        return;
    }

    for (; it != breakpointsAddresses->end(); it++)
        printSingleBreakpoint(it->second);
}

//////////////////////////////////////////////

bool isLabel(string str) {
    if(str.empty())
        return false;

    if (str.find(' ') != string::npos)
        return true;

    if (*(str.rbegin()) == ':')
        return true;
    
    return false;
}

void printSingleInstruction(string line, FILE *file_ptr) {
    fprintf(file_ptr, "%c%s\n", isLabel(line) ? '\n' : '\t', line.c_str());
}

void printSingleLabel(string label, int addr) {
    printf("|%-15s| 0x%04x|\n", label.c_str(), addr);

    return;
}

void printSingleBreakpoint(int addr) {
    printf("Breakpoint at 0x%04x\n", addr);
}
