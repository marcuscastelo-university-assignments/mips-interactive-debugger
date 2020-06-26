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

            if (parentExecutor->getRegisters().hasRegister(instruction_parts[i])) {
                registers.push_back(&parentExecutor->getRegisters().getRegisterByName(instruction_parts[i]));
            } else if (parentExecutor->getProgram().hasLabel(instruction_parts[i])) {
                integers.push_back(parentExecutor->getProgram().getLabelPos(instruction_parts[i])->second * 4);
            } else if (parentExecutor->getRegisters().hasRegister(parseRegisterOffset(instruction_parts[i]).first)) {
                try{
                    integers.push_back(stoi(parseRegisterOffset(instruction_parts[i]).second));
                }
                catch(const std::exception& e) {
                    std::cerr << e.what() << '\n';
                }
                registers.push_back(&parentExecutor->getRegisters().getRegisterByName(parseRegisterOffset(instruction_parts[i]).first));
            }
            else {
                fprintf(stderr, "ERROR: '%s' is neither a register nor a label\n", instruction_parts[i].c_str());
            }
        }
    }

    instruction->feed(registers, integers);

    //TODO: arrumar beqi, div2, div3, etc
    return instruction;
}