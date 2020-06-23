#include "Program.h"
#include "string_utils.h"
#include <stdexcept>

Program::Program() {
    instructions = new vector<string>();
    labelsPosition = new map<string, int>();
    breakpointsPosition = new map<int, bool>();
}

Program::~Program() {
    delete instructions;
    delete labelsPosition;
    delete breakpointsPosition;
}


/////INSTRUCTION/////
void Program::addInstruction(string inst) {
    if (inst.empty())
        return;

    (*instructions).push_back(inst);

    if (isLabel(inst))
        addLabelPos(inst, instructions->size()-1);

    return;
}

string Program::getInstruction(int pos) {
    if (pos < 0 or pos >= (int) instructions->size())
        throw std::out_of_range("Position not allowed");

    return (*instructions)[pos];
}

void Program::printInstructions(string label, FILE *file_ptr) {
    int size = (int) instructions->size();
    
    if (label.empty()) {
        for (int i = 0; i < size; i++)
            printSingleInstruction(getInstruction(i), file_ptr);
        return;
    }

    auto it = getLabelPos(label);
    if (it == labelsPosition->end()) {
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

    if (pos < 0 or pos >= (int) instructions->size())
        throw std::out_of_range("Position not allowed");
    
    if (isLabel(label) == false)
        return;

    label.pop_back();
    printf("label added = %s\n", label.c_str());

    (*labelsPosition)[label] = pos;

    return;
}

map<string,int>::iterator Program::getLabelPos(string label) {
    if (label.empty())
        return labelsPosition->end();

    return labelsPosition->find(label);
}

bool Program::hasLabel(string label) {
    if (label.empty())
        return false;

    return !(getLabelPos(label) == labelsPosition->end());
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

    for (auto it = labelsPosition->begin(); it != labelsPosition->end(); it++) {
        printLine(25);
        printSingleLabel(it->first, it->second);
    }
    printLine(25);        
    
    return;
}

/////BREAKPOINTS/////
void Program::addBreakpoint(int pos) {
    if (pos < 0 or pos >= (int) instructions->size())
        throw std::out_of_range("Position not allowed");

    (*breakpointsPosition)[pos] = true;

    return;
}

void Program::removeBreakpoint(int pos) {
    breakpointsPosition->erase(pos);

    return;
}

bool Program::isBreakpoint(int pos) {
    return (*breakpointsPosition)[pos];
}


//////////////////////////////////////////////

bool isLabel(string str) {
    if(str.empty())
        return false;

    if (*(str.rbegin()) == ':')
        return true;
    
    return false;
}

void printSingleInstruction(string line, FILE *file_ptr) {
    fprintf(file_ptr, "%c%s\n", isLabel(line) ? '\n' : '\t', line.c_str());
}

void printSingleLabel(string label, int pos) {
    printf("|%-15s|%-7d|\n", label.c_str(), pos);

    return;
}