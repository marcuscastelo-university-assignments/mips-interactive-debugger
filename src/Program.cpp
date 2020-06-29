#include "Program.h"
#include "string_utils.h"
#include <stdexcept>

Program::Program() {
    instructions = new std::map<int, std::string>();
    labelsAddresses = new std::map<std::string, int>();
    breakpointsAddresses = new std::map<int, bool>();
}

Program::Program(const Program& program) {
    instructions = new std::map<int, std::string>();
    labelsAddresses = new std::map<std::string, int>();
    breakpointsAddresses = new std::map<int, bool>();
    
    (*instructions) = (*program.instructions);
    (*labelsAddresses) = (*program.labelsAddresses);
    (*breakpointsAddresses) = (*program.breakpointsAddresses);    
}

Program::~Program() {
    delete instructions;
    delete labelsAddresses;
    delete breakpointsAddresses;
}

void Program::clear(std::string what) {
    if (what == "instructions" or what.empty()) {
        delete instructions;
        instructions = new std::map<int, std::string>();
    }

    if (what == "labels" or what.empty()) {
        delete labelsAddresses;
        labelsAddresses = new std::map<std::string, int>();
    }

    if (what == "instructions" or what.empty()) {
        delete breakpointsAddresses;
        breakpointsAddresses = new std::map<int, bool>();
    }    
}

/////INSTRUCTION/////
bool Program::addInstruction(std::string inst) {
    int pos = getInstructionsMapSize();

    if (inst.empty())
        return false;

    if (isLabel(inst) and hasLabel(inst)) {
            printf("Can't have two labels with the same identifier\n");
            return false;
    }

    if (isLabel(inst)) {
        std::vector<std::string> commandParts = split(inst);
        if (commandParts.size() >= 2) {
            printf("Can't have spaces in label's identifier. Ignoring this line: %s\n", inst.c_str());
            return false;
        }

        if (hasLabel(inst)) {
            printf("Can't have two labels with the same identifier\n");
            return false;
        }

        (*instructions)[pos] = inst;
        addLabelPos(inst, pos);
    }

    (*instructions)[pos] = inst;
    
    return true;
}

std::string Program::getInstruction(int pos, bool withCommas) const {
    printf("size: %d\npos: %d\n", getInstructionsMapSize(), pos);
    if (pos < 0 or pos >= (int) getInstructionsMapSize())
        throw std::out_of_range("Position not allowed");

    std::string inst = (*instructions)[pos];
    if (!withCommas) inst = replaceAllChars(inst, ',', ' ');

    return inst;
}

size_t Program::getInstructionsMapSize(void) const {
    return instructions->size()*4;
}   

void Program::printInstructions(std::string label, FILE *file_ptr) const {
    int size = (int) getInstructionsMapSize();
    
    if (label.empty()) {
        for (int i = 0; i < size; i += 4)
            printSingleInstruction(getInstruction(i, true), i, file_ptr);
        return;
    }

    auto it = getLabelPos(label);
    if (it == labelsAddresses->end()) {
        printf("Label %s undefined\n", label.c_str());
        return;
    }

    printSingleInstruction(getInstruction(it->second, true), it->second, file_ptr);
    for (int i = it->second+1; i < size; i += 4) {
        std::string inst = getInstruction(i, true);
        if (isLabel(inst))
            break;
        
        printSingleInstruction(inst, i, file_ptr);
    }  

    return;
}


/////LABEL/////
void Program::addLabelPos(std::string label, int pos) {
    if (label.empty())
        return;

    if (pos < 0 or pos >= (int) getInstructionsMapSize())
        throw std::out_of_range("Position not allowed");
    
    if (isLabel(label) == false)
        return;

    label.pop_back();

    (*labelsAddresses)[label] = pos;

    return;
}

std::map<std::string,int>::iterator Program::getLabelPos(const std::string& label) const {
    if (label.empty())
        return labelsAddresses->end();

    return labelsAddresses->find(label);
}

bool Program::hasLabel(std::string label) const {
    if (label.empty())
        return false;

    if (label[label.size()-1] == ':')
        label.pop_back();

    return !(getLabelPos(label) == labelsAddresses->end());
}

void Program::printLabel(std::string label) const {
    if (label.empty() == false) {
        if (hasLabel(label)) {
            printLine(25);    
            printSingleLabel(label, (getLabelPos(label)->second)*4);
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
    if (pos < 0 or pos >= (int) getInstructionsMapSize())
        throw std::out_of_range("Position not allowed");

    (*breakpointsAddresses)[pos] = true;

    return;
}

void Program::removeBreakpoint(int pos) {
    breakpointsAddresses->erase(pos);

    return;
}

bool Program::isBreakpoint(int pos) const {
    return !(breakpointsAddresses->find(pos) == breakpointsAddresses->end()); 
}

void Program::printBreakpoints(void) const {
    auto it = breakpointsAddresses->begin();
    
    int size = breakpointsAddresses->size();
    printf("size: %d\n", size);

    if (breakpointsAddresses->end() == it) {
        printf("No breakpoints added\n");
        return;
    }

    for (; it != breakpointsAddresses->end(); it++)
        printSingleBreakpoint((it->first)*4);
}

//////////////////////////////////////////////

bool isLabel(std::string str) {
    if(str.empty())
        return false;
    
    if (*(str.rbegin()) == ':')
        return true;
    
    return false;
}

void printSingleInstruction(std::string line, int pos, FILE *file_ptr) {
    if (isLabel(line))
        fprintf(file_ptr, "%c0x%04x", '\n', pos);
    else
        fprintf(file_ptr, "0x%04x%c", pos, '\t');

    fprintf(file_ptr, "%c%s\n", '\t', line.c_str());
}

void printSingleLabel(std::string label, int addr) {
    printf("|%-15s| 0x%04x|\n", label.c_str(), addr);

    return;
}

void printSingleBreakpoint(int addr) {
    printf("Breakpoint at 0x%04x\n", addr);
}
