#include "Interpreter.h"
#include "MipsInstructions.h"

#include <vector>
#include <iostream>
#include <stdexcept>
#include "string_utils.h"

Interpreter::Interpreter(Executor *parentExecutor) 
: parentExecutor(parentExecutor) 
{}

Instruction *Interpreter::interpretInstruction(const std::string& instructionStr) const {
    std::vector<std::string> instruction_parts = split(instructionStr);
    std::vector<Register*> registers;
    std::vector<int> integers;

    if (isLabel(instructionStr)) return MipsInstructions::getInstructionByName("label");

    //TODO: no_advance
    if (instruction_parts.size() < 1) return MipsInstructions::getInstructionByName("invalid");

    Instruction *instruction = MipsInstructions::getInstructionByName(instruction_parts[0]);
    if (instruction == NULL) return MipsInstructions::getInstructionByName("invalid");

    for (unsigned i = 1; i < instruction_parts.size(); i++) {
        if (isInteger(instruction_parts[i])) {
            try {
                integers.push_back(stoi(instruction_parts[i]));
            }
            catch(const std::exception& e) {
                std::cerr << e.what() << '\n';
            }   
        }
        else { //TODO: implement label
            try {
                Register &reg = parentExecutor->getRegisters().getRegisterByName(instruction_parts[i]);
                registers.push_back(&reg);
            } catch (const std::invalid_argument& e) {
                fprintf(stderr, "ERROR: invalid register provided: '%s'\n", instruction_parts[i].c_str());
                std::cout << e.what() << std::endl;
            }
        }
    }

    instruction->feed(registers, integers);

    //TODO: arrumar beqi, div2, div3, etc
    return instruction;
}